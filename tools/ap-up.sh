#!/bin/sh
# ap-up.sh start [-n] | stop | status - Wi-Fi hotspot on ap0, next to wlan0
# (after wifi-up.sh). /etc/ap.conf sets AP_SSID and AP_PSK (8-63 characters).
#   start     ap0 on wlan0's channel, WPA2-PSK through wpa_supplicant, DHCP
#             from dnsmasq; clients get no default route
#   start -n  also shares wlan0's uplink: IPv4 forwarding, an nftables
#             masquerade, and dnsmasq as router and DNS (needs netfilter)
#   stop      removes ap0; wlan0 stays up
CONF=${AP_CONF:-/etc/ap.conf}
RUN=/run/ap-up
NET=192.168.43

stop() {
	for p in dnsmasq wpa; do
		[ -f $RUN/$p.pid ] || continue
		pid=$(cat $RUN/$p.pid)
		kill "$pid" 2>/dev/null
		for i in 1 2 3 4 5; do
			kill -0 "$pid" 2>/dev/null || break
			sleep 1
		done
	done
	if nft list table ip hotspot > /dev/null 2>&1; then
		nft delete table ip hotspot
		sysctl -qw net.ipv4.ip_forward=0
	fi
	# "1" with Wi-Fi on drops ap0/p2p0 and keeps the station
	[ -d /sys/class/net/ap0 ] && echo 1 > /dev/wmtWifi
	rm -rf $RUN
}

fail() {
	echo "ap-up: $*" >&2
	stop
	exit 1
}

status() {
	if [ ! -d /sys/class/net/ap0 ]; then
		echo "ap0: down"
		return
	fi
	wpa_cli -p $RUN/ctrl -i ap0 status | grep -E '^(ssid|freq|wpa_state)='
	echo "clients: $(wpa_cli -p $RUN/ctrl -i ap0 all_sta | grep -cE '^([0-9a-f]{2}:){5}')"
	if nft list table ip hotspot > /dev/null 2>&1; then
		echo "uplink: shared from wlan0"
	else
		echo "uplink: not shared"
	fi
}

start() {
	[ -d /sys/class/net/wlan0 ] || { echo "ap-up: no wlan0, run wifi-up.sh first" >&2; exit 1; }
	[ -d /sys/class/net/ap0 ] && { echo "ap-up: ap0 is already up" >&2; exit 1; }
	[ -f "$CONF" ] && . "$CONF"
	if [ -z "$AP_SSID" ] || [ ${#AP_PSK} -lt 8 ] || [ ${#AP_PSK} -gt 63 ]; then
		echo "ap-up: $CONF must set AP_SSID and an 8-63 character AP_PSK" >&2
		exit 1
	fi

	# one radio: the AP takes the station's channel
	freq=$(iw dev wlan0 link | awk '/freq:/ { print int($2) }')
	[ -n "$freq" ] || freq=2437

	mkdir -p $RUN && chmod 700 $RUN
	cat > $RUN/wpa.conf <<EOF
ctrl_interface=$RUN/ctrl
network={
	ssid="$AP_SSID"
	mode=2
	frequency=$freq
	key_mgmt=WPA-PSK
	proto=RSN
	pairwise=CCMP
	group=CCMP
	psk="$AP_PSK"
}
EOF

	echo A > /dev/wmtWifi || fail "/dev/wmtWifi refused AP mode"
	for i in $(seq 1 20); do
		[ -d /sys/class/net/ap0 ] && break
		sleep 1
	done
	[ -d /sys/class/net/ap0 ] || fail "ap0 did not appear"
	ip addr add $NET.1/24 dev ap0

	wpa_supplicant -B -s -i ap0 -D nl80211 -c $RUN/wpa.conf -P $RUN/wpa.pid ||
		fail "wpa_supplicant did not start"
	for i in $(seq 1 15); do
		wpa_cli -p $RUN/ctrl -i ap0 status 2>/dev/null | grep -q '^wpa_state=COMPLETED' && break
		sleep 1
	done
	wpa_cli -p $RUN/ctrl -i ap0 status 2>/dev/null | grep -q '^wpa_state=COMPLETED' ||
		fail "the AP did not come up"

	# without the uplink: DHCP only, and an empty router option so clients
	# keep their own default route
	dns="--port=0 --dhcp-option=3"
	if [ "$1" = -n ]; then
		sysctl -qw net.ipv4.ip_forward=1
		nft -f - <<EOF || fail "nft failed (netfilter in the kernel? nftables installed?)"
table ip hotspot {
	chain postrouting {
		type nat hook postrouting priority srcnat;
		ip saddr $NET.0/24 oifname "wlan0" masquerade
	}
}
EOF
		dns=
	fi
	dnsmasq --interface=ap0 --bind-interfaces --except-interface=lo $dns \
		--dhcp-range=$NET.10,$NET.50,12h --pid-file=$RUN/dnsmasq.pid ||
		fail "dnsmasq did not start"
	status
}

case "$1" in
start)	start "$2" ;;
stop)	stop ;;
status)	status ;;
*)	echo "usage: ap-up.sh start [-n] | stop | status" >&2; exit 1 ;;
esac
