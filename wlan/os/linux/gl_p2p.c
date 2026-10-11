/*
** Id: @(#) gl_p2p.c@@
*/

/*! \file   gl_p2p.c
    \brief  Main routines of Linux driver interface for Wi-Fi Direct

    This file contains the main routines of Linux driver for MediaTek Inc. 802.11
    Wireless LAN Adapters.
*/

/*
** Log: gl_p2p.c
**
** 09 12 2012 wcpadmin
** [ALPS00276400] Remove MTK copyright and legal header on GPL/LGPL related packages
** .
**
** 08 17 2012 yuche.tsai
** NULL
** Fix compile warning.
**
** 08 16 2012 yuche.tsai
** NULL
** Fix compile warning.
**
** 08 14 2012 yuche.tsai
** NULL
** FPB from ALPS.JB to phase 2 release.
**
** 07 26 2012 yuche.tsai
** [ALPS00324337] [ALPS.JB][Hot-Spot] Driver update for Hot-Spot
** Update driver code of ALPS.JB for hot-spot.
**
** 07 19 2012 yuche.tsai
** NULL
** Code update for JB.
 *
 * 07 17 2012 yuche.tsai
 * NULL
 * Fix compile error for JB.
 *
 * 07 17 2012 yuche.tsai
 * NULL
 * Let netdev bring up.
 *
 * 07 17 2012 yuche.tsai
 * NULL
 * Compile no error before trial run.
 *
 * 01 09 2012 terry.wu
 * [WCXRP00001166] [Wi-Fi] [Driver] cfg80211 integration for p2p newtork
 * cfg80211 integration for p2p network.
 *
 * 12 19 2011 terry.wu
 * [WCXRP00001142] [Wi-Fi] [P2P Driver] XOR local admin bit to generate p2p net device MAC
 * XOR local administrated bit to generate net device MAC of p2p network.
 *
 * 12 02 2011 yuche.tsai
 * NULL
 * Fix possible KE when unload p2p.
 *
 * 11 24 2011 yuche.tsai
 * NULL
 * Fix P2P IOCTL of multicast address bug, add low power driver stop control.
 *
 * 11 22 2011 yuche.tsai
 * NULL
 * Update RSSI link quality of P2P Network query method. (Bug fix)
 *
 * 11 19 2011 yuche.tsai
 * NULL
 * Add RSSI support for P2P network.
 *
 * 11 16 2011 yuche.tsai
 * [WCXRP00001107] [Volunteer Patch][Driver] Large Network Type index assert in FW issue.
 * Avoid using work thread in set p2p multicast address callback.
 *
 * 11 11 2011 yuche.tsai
 * NULL
 * Fix work thread cancel issue.
 *
 * 11 11 2011 yuche.tsai
 * NULL
 * Fix default device name issue.
 *
 * 11 08 2011 yuche.tsai
 * [WCXRP00001094] [Volunteer Patch][Driver] Driver version & supplicant version query & set support for service
 * discovery version check.
 * Add support for driver version query & p2p supplicant verseion set.
 * For new service discovery mechanism sync.
 *
 * 11 07 2011 yuche.tsai
 * NULL
 * [ALPS 00087243] KE in worker thread.
 * The multicast address list is scheduled in worker thread.
 * Before the worker thread is excuted, if P2P is unloaded, a KE may occur.
 *
 * 10 26 2011 terry.wu
 * [WCXRP00001066] [MT6620 Wi-Fi] [P2P Driver] Fix P2P Oid Issue
 * Fix some P2P OID functions didn't raise its flag "fgIsP2pOid" issue.
 *
 * 10 25 2011 cm.chang
 * [WCXRP00001058] [All Wi-Fi][Driver] Fix sta_rec's phyTypeSet and OBSS scan in AP mode
 * .
 *
 * 10 18 2011 yuche.tsai
 * [WCXRP00001045] [WiFi Direct][Driver] Check 2.1 branch.
 * Support Channel Query.
 *
 * 10 18 2011 yuche.tsai
 * [WCXRP00001045] [WiFi Direct][Driver] Check 2.1 branch.
 * New 2.1 branch

 *
 * 08 26 2011 yuche.tsai
 * NULL
 * Fix bug of parsing secondary device list type issue.
 *
 * 08 24 2011 yuche.tsai
 * [WCXRP00000919] [Volunteer Patch][WiFi Direct][Driver] Invitation New Feature.
 * Invitation Abort.
 *
 * 08 23 2011 yuche.tsai
 * NULL
 * Fix multicast address list issue of P2P.
 *
 * 08 22 2011 chinglan.wang
 * NULL
 * Fix invitation indication bug..
 *
 * 08 16 2011 cp.wu
 * [WCXRP00000934] [MT6620 Wi-Fi][Driver][P2P] Wi-Fi hot spot with auto sparse channel residence
 * auto channel decision for 2.4GHz hot spot mode
 *
 * 08 16 2011 chinglan.wang
 * NULL
 * Add the group id information in the invitation indication.
 *
 * 08 09 2011 yuche.tsai
 * [WCXRP00000919] [Volunteer Patch][WiFi Direct][Driver] Invitation New Feature.
 * Invitation Feature add on.
 *
 * 08 05 2011 yuche.tsai
 * [WCXRP00000856] [Volunteer Patch][WiFi Direct][Driver] MT6620 WiFi Direct IOT Issue with BCM solution.
 * Add Password ID check for quick connection.
 * Also modify some connection policy.
 *
 * 07 18 2011 chinglan.wang
 * NULL
 * Add IOC_P2P_GO_WSC_IE (p2p capability).
 *
 * 06 14 2011 yuche.tsai
 * NULL
 * Add compile flag to disable persistent group support.
 *
 * 05 04 2011 chinglan.wang
 * [WCXRP00000698] [MT6620 Wi-Fi][P2P][Driver] Add p2p invitation command for the p2p driver
 * .
 *
 * 05 02 2011 yuche.tsai
 * [WCXRP00000693] [Volunteer Patch][MT6620][Driver] Clear Formation Flag after TX lifetime timeout.
 * Clear formation flag after formation timeout.
 *
 * 04 22 2011 george.huang
 * [WCXRP00000621] [MT6620 Wi-Fi][Driver] Support P2P supplicant to set power mode
 * .
 *
 * 04 21 2011 george.huang
 * [WCXRP00000621] [MT6620 Wi-Fi][Driver] Support P2P supplicant to set power mode
 * 1. Revise P2P power mode setting.
 * 2. Revise fast-PS for concurrent
 *
 * 04 19 2011 wh.su
 * NULL
 * Adding length check before doing WPA RSN IE parsing for scan results indicate.
 *
 * 04 14 2011 yuche.tsai
 * [WCXRP00000646] [Volunteer Patch][MT6620][FW/Driver] Sigma Test Modification for some test case.
 * Connection flow refine for Sigma test.
 *
 * 04 08 2011 yuche.tsai
 * [WCXRP00000624] [Volunteer Patch][MT6620][Driver] Add device discoverability support for GO.
 * Add device discoverability support.
 *
 * 04 08 2011 george.huang
 * [WCXRP00000621] [MT6620 Wi-Fi][Driver] Support P2P supplicant to set power mode
 * separate settings of P2P and AIS
 *
 * 04 07 2011 terry.wu
 * [WCXRP00000619] [MT6620 Wi-Fi][Driver] fix kernel panic may occur when removing wlan
 * Fix kernel panic may occur when removing wlan driver.
 *
 * 03 31 2011 wh.su
 * [WCXRP00000614] [MT6620 Wi-Fi][Driver] P2P: Update beacon content while setting WSC IE
 * Update the wsc ie to beacon content.
 *
 * 03 25 2011 wh.su
 * NULL
 * add the sample code for set power mode and get power mode.
 *
 * 03 25 2011 yuche.tsai
 * NULL
 * Improve some error handleing.
 *
 * 03 22 2011 george.huang
 * [WCXRP00000504] [MT6620 Wi-Fi][FW] Support Sigma CAPI for power saving related command
 * link with supplicant commands
 *
 * 03 22 2011 yuche.tsai
 * [WCXRP00000584] [Volunteer Patch][MT6620][Driver] Add beacon timeout support for WiFi Direct.
 * Modify formation policy.
 *
 * 03 22 2011 yuche.tsai
 * NULL
 * Modify formation policy setting.
 *
 * 03 18 2011 yuche.tsai
 * [WCXRP00000574] [Volunteer Patch][MT6620][Driver] Modify P2P FSM Connection Flow
 * Modify connection flow after Group Formation Complete, or device connect to a GO.
 * Instead of request channel & connect directly, we use scan to allocate channel bandwidth & connect after RX BCN.
 *
 * 03 15 2011 wh.su
 * [WCXRP00000563] [MT6620 Wi-Fi] [P2P] Set local config method while set password Id ready
 * set lccal config method method while set password Id ready.
 *
 * 03 15 2011 yuche.tsai
 * [WCXRP00000560] [Volunteer Patch][MT6620][Driver] P2P Connection from UI using KEY/DISPLAY issue
 * Fix some configure method issue.
 *
 * 03 15 2011 jeffrey.chang
 * [WCXRP00000558] [MT6620 Wi-Fi][MT6620 Wi-Fi][Driver] refine the queue selection algorithm for WMM
 * refine queue_select function
 *
 * 03 13 2011 wh.su
 * [WCXRP00000530] [MT6620 Wi-Fi] [Driver] skip doing p2pRunEventAAAComplete after send assoc response Tx Done
 * add code for avoid compiling warning.
 *
 * 03 10 2011 yuche.tsai
 * NULL
 * Add P2P API.
 *
 * 03 10 2011 terry.wu
 * [WCXRP00000505] [MT6620 Wi-Fi][Driver/FW] WiFi Direct Integration
 * Remove unnecessary assert and message.
 *
 * 03 08 2011 wh.su
 * [WCXRP00000488] [MT6620 Wi-Fi][Driver] Support the SIGMA set p2p parameter to driver
 * support the power save related p2p setting.
 *
 * 03 07 2011 wh.su
 * [WCXRP00000506] [MT6620 Wi-Fi][Driver][FW] Add Security check related code
 * rename the define to anti_pviracy.
 *
 * 03 05 2011 wh.su
 * [WCXRP00000506] [MT6620 Wi-Fi][Driver][FW] Add Security check related code
 * add the code to get the check rsponse and indicate to app.
 *
 * 03 03 2011 jeffrey.chang
 * [WCXRP00000512] [MT6620 Wi-Fi][Driver] modify the net device relative functions to support the H/W multiple queue
 * support concurrent network
 *
 * 03 03 2011 jeffrey.chang
 * [WCXRP00000512] [MT6620 Wi-Fi][Driver] modify the net device relative functions to support the H/W multiple queue
 * modify P2P's netdevice  functions to support multiple H/W queues
 *
 * 03 03 2011 cp.wu
 * [WCXRP00000283] [MT6620 Wi-Fi][Driver][Wi-Fi Direct] Implementation of interface for supporting Wi-Fi Direct Service
 * Discovery
 * for get request, the buffer length to be copied is header + payload.
 *
 * 03 02 2011 wh.su
 * [WCXRP00000506] [MT6620 Wi-Fi][Driver][FW] Add Security check related code
 * add code to let the beacon and probe response for Auto GO WSC .
 *
 * 03 02 2011 cp.wu
 * [WCXRP00000283] [MT6620 Wi-Fi][Driver][Wi-Fi Direct] Implementation of interface for supporting Wi-Fi Direct Service
 * Discovery
 * add a missed break.
 *
 * 03 01 2011 yuche.tsai
 * [WCXRP00000501] [Volunteer Patch][MT6620][Driver] No common channel issue when doing GO formation
 * Update channel issue when doing GO formation..
 *
 * 02 25 2011 wh.su
 * [WCXRP00000488] [MT6620 Wi-Fi][Driver] Support the SIGMA set p2p parameter to driver
 * add the Operation channel setting.
 *
 * 02 23 2011 wh.su
 * [WCXRP00000488] [MT6620 Wi-Fi][Driver] Support the SIGMA set p2p parameter to driver
 * fixed the set int ioctl set index and value map to driver issue.
 *
 * 02 22 2011 wh.su
 * [WCXRP00000488] [MT6620 Wi-Fi][Driver] Support the SIGMA set p2p parameter to driver
 * adding the ioctl set int from supplicant, and can used to set the p2p parameters
 *
 * 02 21 2011 terry.wu
 * [WCXRP00000476] [MT6620 Wi-Fi][Driver] Clean P2P scan list while removing P2P
 * Clean P2P scan list while removing P2P.
 *
 * 02 18 2011 wh.su
 * [WCXRP00000471] [MT6620 Wi-Fi][Driver] Add P2P Provison discovery append Config Method attribute at WSC IE
 * fixed the ioctl setting that index not map to spec defined config method.
 *
 * 02 17 2011 wh.su
 * [WCXRP00000471] [MT6620 Wi-Fi][Driver] Add P2P Provison discovery append Config Method attribute at WSC IE
 * append the WSC IE config method attribute at provision discovery request.
 *
 * 02 17 2011 wh.su
 * [WCXRP00000448] [MT6620 Wi-Fi][Driver] Fixed WSC IE not send out at probe request
 * modify the structure pointer for set WSC IE.
 *
 * 02 16 2011 wh.su
 * [WCXRP00000448] [MT6620 Wi-Fi][Driver] Fixed WSC IE not send out at probe request
 * fixed the probe request send out without WSC IE issue (at P2P).
 *
 * 02 09 2011 cp.wu
 * [WCXRP00000283] [MT6620 Wi-Fi][Driver][Wi-Fi Direct] Implementation of interface for supporting Wi-Fi Direct Service
 * Discovery
 * fix typo
 *
 * 02 09 2011 yuche.tsai
 * [WCXRP00000431] [Volunteer Patch][MT6620][Driver] Add MLME support for deauthentication under AP(Hot-Spot) mode.
 * Add Support for MLME deauthentication for Hot-Spot.
 *
 * 01 25 2011 terry.wu
 * [WCXRP00000393] [MT6620 Wi-Fi][Driver] Add new module insert parameter
 * Add a new module parameter to indicate current runnig mode, P2P or AP.
 *
 * 01 12 2011 yuche.tsai
 * [WCXRP00000352] [Volunteer Patch][MT6620][Driver] P2P Statsion Record Client List Issue
 * 1. Modify Channel Acquire Time of AP mode from 5s to 1s.
 * 2. Call cnmP2pIsPermit() before active P2P network.
 * 3. Add channel selection support for AP mode.
 *
 * 01 05 2011 cp.wu
 * [WCXRP00000283] [MT6620 Wi-Fi][Driver][Wi-Fi Direct] Implementation of interface for supporting Wi-Fi Direct Service
 * Discovery
 * ioctl implementations for P2P Service Discovery
 *
 * 01 04 2011 cp.wu
 * [WCXRP00000338] [MT6620 Wi-Fi][Driver] Separate kalMemAlloc into kmalloc and vmalloc implementations to ease
 * physically continuous memory demands
 * separate kalMemAlloc() into virtually-continuous and physically-continuous type to ease slab system pressure
 *
 * 12 22 2010 cp.wu
 * [WCXRP00000283] [MT6620 Wi-Fi][Driver][Wi-Fi Direct] Implementation of interface for supporting Wi-Fi Direct Service
 * Discovery
 * 1. header file restructure for more clear module isolation
 * 2. add function interface definition for implementing Service Discovery callbacks
 *
 * 12 15 2010 cp.wu
 * NULL
 * invoke nicEnableInterrupt() before leaving from wlanAdapterStart()
 *
 * 12 08 2010 yuche.tsai
 * [WCXRP00000245] [MT6620][Driver] Invitation & Provision Discovery Feature Check-in
 * [WCXRP000000245][MT6620][Driver] Invitation Request Feature Add
 *
 * 11 30 2010 yuche.tsai
 * NULL
 * Invitation & Provision Discovery Indication.
 *
 * 11 17 2010 wh.su
 * [WCXRP00000164] [MT6620 Wi-Fi][Driver] Support the p2p random SSID[WCXRP00000179] [MT6620 Wi-Fi][FW] Set the Tx
 * lowest rate at wlan table for normal operation
 * fixed some ASSERT check.
 *
 * 11 04 2010 wh.su
 * [WCXRP00000164] [MT6620 Wi-Fi][Driver] Support the p2p random SSID
 * adding the p2p random ssid support.
 *
 * 10 20 2010 wh.su
 * [WCXRP00000124] [MT6620 Wi-Fi] [Driver] Support the dissolve P2P Group
 * Add the code to support disconnect p2p group
 *
 * 10 04 2010 wh.su
 * [WCXRP00000081] [MT6620][Driver] Fix the compiling error at WinXP while enable P2P
 * add a kal function for set cipher.
 *
 * 10 04 2010 wh.su
 * [WCXRP00000081] [MT6620][Driver] Fix the compiling error at WinXP while enable P2P
 * fixed compiling error while enable p2p.
 *
 * 09 28 2010 wh.su
 * NULL
 * [WCXRP00000069][MT6620 Wi-Fi][Driver] Fix some code for phase 1 P2P Demo.
 *
 * 09 21 2010 kevin.huang
 * [WCXRP00000054] [MT6620 Wi-Fi][Driver] Restructure driver for second Interface
 * Isolate P2P related function for Hardware Software Bundle
 *
 * 09 21 2010 kevin.huang
 * [WCXRP00000052] [MT6620 Wi-Fi][Driver] Eliminate Linux Compile Warning
 * Eliminate Linux Compile Warning
 *
 * 09 10 2010 george.huang
 * NULL
 * update iwpriv LP related
 *
 * 09 10 2010 wh.su
 * NULL
 * fixed the compiling error at win XP.
 *
 * 09 09 2010 cp.wu
 * NULL
 * add WPS/WPA/RSN IE for Wi-Fi Direct scanning result.
 *
 * 09 07 2010 wh.su
 * NULL
 * adding the code for beacon/probe req/ probe rsp wsc ie at p2p.
 *
 * 09 06 2010 wh.su
 * NULL
 * let the p2p can set the privacy bit at beacon and rsn ie at assoc req at key handshake state.
 *
 * 08 25 2010 cp.wu
 * NULL
 * add netdev_ops(NDO) for linux kernel 2.6.31 or greater
 *
 * 08 23 2010 cp.wu
 * NULL
 * revise constant definitions to be matched with implementation (original cmd-event definition is deprecated)
 *
 * 08 20 2010 cp.wu
 * NULL
 * correct typo.
 *
 * 08 20 2010 yuche.tsai
 * NULL
 * Invert Connection request provision status parameter.
 *
 * 08 19 2010 cp.wu
 * NULL
 * add set mac address interface for further possibilities of wpa_supplicant overriding interface address.
 *
 * 08 18 2010 cp.wu
 * NULL
 * modify pwp ioctls attribution by removing FIXED_SIZE.
 *
 * 08 18 2010 jeffrey.chang
 * NULL
 * support multi-function sdio
 *
 * 08 17 2010 cp.wu
 * NULL
 * correct p2p net device registration with NULL pointer access issue.
 *
 * 08 16 2010 cp.wu
 * NULL
 * P2P packets are now marked when being queued into driver, and identified later without checking MAC address
 *
 * 08 16 2010 cp.wu
 * NULL
 * add subroutines for P2P to set multicast list.
 *
 * 08 16 2010 george.huang
 * NULL
 * add wext handlers to link P2P set PS profile/ network address function (TBD)
 *
 * 08 16 2010 cp.wu
 * NULL
 * revised implementation of Wi-Fi Direct io controls.
 *
 * 08 12 2010 cp.wu
 * NULL
 * follow-up with ioctl interface update for Wi-Fi Direct application
 *
 * 08 06 2010 cp.wu
 * NULL
 * driver hook modifications corresponding to ioctl interface change.
 *
 * 08 03 2010 cp.wu
 * NULL
 * add basic support for ioctl of getting scan result. (only address and SSID are reporterd though)
 *
 * 08 03 2010 cp.wu
 * NULL
 * [Wi-Fi Direct Driver Hook] change event indication API to be consistent with supplicant
 *
 * 08 03 2010 cp.wu
 * NULL
 * surpress compilation warning.
 *
 * 08 03 2010 cp.wu
 * NULL
 * [Wi-Fi Direct] add framework for driver hooks
 *
 * 07 08 2010 cp.wu
 *
 * [WPD00003833] [MT6620 and MT5931] Driver migration - move to new repository.
 *
 * 06 23 2010 cp.wu
 * [WPD00003833][MT6620 and MT5931] Driver migration
 * p2p interface revised to be sync. with HAL
 *
 * 06 06 2010 kevin.huang
 * [WPD00003832][MT6620 5931] Create driver base
 * [MT6620 5931] Create driver base
 *
 * 06 01 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * add ioctl to configure scan mode for p2p connection
 *
 * 05 31 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * add cfg80211 interface, which is to replace WE, for further extension
 *
 * 05 17 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * implement private io controls for Wi-Fi Direct
 *
 * 05 17 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * implement get scan result.
 *
 * 05 17 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * add basic handling framework for wireless extension ioctls.
 *
 * 05 17 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * 1) add timeout handler mechanism for pending command packets
 * 2) add p2p add/removal key
 *
 * 05 14 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * implement wireless extension ioctls in iw_handler form.
 *
 * 05 14 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * add ioctl framework for Wi-Fi Direct by reusing wireless extension ioctls as well
 *
 * 05 11 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * p2p ioctls revised.
 *
 * 05 11 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * add ioctl for controlling p2p scan phase parameters
 *
 * 05 10 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * implement basic wi-fi direct framework
 *
 * 05 07 2010 cp.wu
 * [WPD00003831][MT6620 Wi-Fi] Add framework for Wi-Fi Direct support
 * add basic framework for implementating P2P driver hook.
 *
**
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include <linux/poll.h>
#include <linux/kmod.h>

#include "gl_os.h"
#include "wlan_lib.h"
#include "gl_wext.h"
#include "gl_p2p_os.h"
#include "gl_p2p_ioctl.h"
#include "gl_vendor.h"

#include "precomp.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define ARGV_MAX_NUM        (4)

/*For CFG80211 - wiphy parameters*/
#define MAX_SCAN_LIST_NUM   (1)
#define MAX_SCAN_IE_LEN     (512)

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

#if CFG_ENABLE_WIFI_DIRECT_CFG_80211
static struct cfg80211_ops mtk_p2p_ops = {
	.change_virtual_intf = mtk_p2p_cfg80211_change_iface,	/* 1st */
	.change_bss = mtk_p2p_cfg80211_change_bss,
	.scan = mtk_p2p_cfg80211_scan,
	.remain_on_channel = mtk_p2p_cfg80211_remain_on_channel,
	.cancel_remain_on_channel = mtk_p2p_cfg80211_cancel_remain_on_channel,
	.mgmt_tx = mtk_p2p_cfg80211_mgmt_tx,
	.connect = mtk_p2p_cfg80211_connect,
	.disconnect = mtk_p2p_cfg80211_disconnect,
	.deauth = mtk_p2p_cfg80211_deauth,
	.disassoc = mtk_p2p_cfg80211_disassoc,
	.start_ap = mtk_p2p_cfg80211_start_ap,
	.change_beacon = mtk_p2p_cfg80211_change_beacon,
	.stop_ap = mtk_p2p_cfg80211_stop_ap,
	.set_wiphy_params = mtk_p2p_cfg80211_set_wiphy_params,
	.del_station = mtk_p2p_cfg80211_del_station,
	.set_bitrate_mask = mtk_p2p_cfg80211_set_bitrate_mask,
	.update_mgmt_frame_registrations = mtk_p2p_cfg80211_update_mgmt_frame_registrations,
	.get_station = mtk_p2p_cfg80211_get_station,
	.add_key = mtk_p2p_cfg80211_add_key,
	.get_key = mtk_p2p_cfg80211_get_key,
	.del_key = mtk_p2p_cfg80211_del_key,
	.set_default_key = mtk_p2p_cfg80211_set_default_key,
	.join_ibss = mtk_p2p_cfg80211_join_ibss,
	.leave_ibss = mtk_p2p_cfg80211_leave_ibss,
	.set_tx_power = mtk_p2p_cfg80211_set_txpower,
	.get_tx_power = mtk_p2p_cfg80211_get_txpower,
	.set_power_mgmt = mtk_p2p_cfg80211_set_power_mgmt,
#ifdef CONFIG_NL80211_TESTMODE
	.testmode_cmd = mtk_p2p_cfg80211_testmode_cmd,
#endif
};

static const struct wiphy_vendor_command mtk_p2p_vendor_ops[] = {
	{
		{
			.vendor_id = GOOGLE_OUI,
			.subcmd = WIFI_SUBCMD_GET_CHANNEL_LIST
		},
		.flags = WIPHY_VENDOR_CMD_NEED_WDEV | WIPHY_VENDOR_CMD_NEED_NETDEV,
		.policy = VENDOR_CMD_RAW_DATA,
		.doit = mtk_cfg80211_vendor_get_channel_list
	},
	{
		{
			.vendor_id = GOOGLE_OUI,
			.subcmd = WIFI_SUBCMD_SET_COUNTRY_CODE
		},
		.flags = WIPHY_VENDOR_CMD_NEED_WDEV | WIPHY_VENDOR_CMD_NEED_NETDEV,
		.policy = VENDOR_CMD_RAW_DATA,
		.doit = mtk_cfg80211_vendor_set_country_code
	},
};

/* There isn't a lot of sense in it, but you can transmit anything you like */
static const struct ieee80211_txrx_stypes
	mtk_cfg80211_default_mgmt_stypes[NUM_NL80211_IFTYPES] = {
	[NL80211_IFTYPE_ADHOC] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4)
	},
	[NL80211_IFTYPE_STATION] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) | BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	},
	[NL80211_IFTYPE_AP] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_PROBE_REQ >> 4) | BIT(IEEE80211_STYPE_ACTION >> 4)
	},
	[NL80211_IFTYPE_AP_VLAN] = {
		/* copy AP */
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
		      BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
		      BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		      BIT(IEEE80211_STYPE_AUTH >> 4) |
		      BIT(IEEE80211_STYPE_DEAUTH >> 4) | BIT(IEEE80211_STYPE_ACTION >> 4)
	},
	[NL80211_IFTYPE_P2P_CLIENT] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) | BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	},
	[NL80211_IFTYPE_P2P_GO] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_PROBE_REQ >> 4) | BIT(IEEE80211_STYPE_ACTION >> 4)
	}
};

#endif

#ifdef CONFIG_PM
static const struct wiphy_wowlan_support p2p_wowlan_support = {
	.flags = WIPHY_WOWLAN_DISCONNECT | WIPHY_WOWLAN_ANY,
};
#endif

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
/* for IE Searching */
extern BOOLEAN
wextSrchDesiredWPAIE(IN PUINT_8 pucIEStart,
		     IN INT_32 i4TotalIeLen, IN UINT_8 ucDesiredElemId, OUT PUINT_8 *ppucDesiredIE);

#if CFG_SUPPORT_WPS
extern BOOLEAN
wextSrchDesiredWPSIE(IN PUINT_8 pucIEStart,
		     IN INT_32 i4TotalIeLen, IN UINT_8 ucDesiredElemId, OUT PUINT_8 *ppucDesiredIE);
#endif

/* Net Device Hooks */
static int p2pOpen(IN struct net_device *prDev);

static int p2pStop(IN struct net_device *prDev);

static struct net_device_stats *p2pGetStats(IN struct net_device *prDev);

static void p2pSetMulticastList(IN struct net_device *prDev);

static int p2pHardStartXmit(IN struct sk_buff *prSkb, IN struct net_device *prDev);

static int p2pSetMACAddress(IN struct net_device *prDev, void *addr);

/*----------------------------------------------------------------------------*/
/*!
* \brief Override the implementation of select queue
*
* \param[in] dev Pointer to struct net_device
* \param[in] skb Pointer to struct skb_buff
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/

unsigned int _p2p_cfg80211_classify8021d(struct sk_buff *skb)
{
	unsigned int dscp = 0;

	/* skb->priority values from 256->263 are magic values
	 * directly indicate a specific 802.1d priority.  This is
	 * to allow 802.1d priority to be passed directly in from
	 * tags
	 */

	if (skb->priority >= 256 && skb->priority <= 263)
		return skb->priority - 256;
	switch (skb->protocol) {
	case htons(ETH_P_IP):
		dscp = ip_hdr(skb)->tos & 0xfc;
		break;
	}
	return dscp >> 5;
}

static const UINT_16 au16Wlan1dToQueueIdx[8] = { 1, 0, 0, 1, 2, 2, 3, 3 };

static UINT_16 p2pSelectQueue(struct net_device *dev, struct sk_buff *skb,
				struct net_device *sb_dev)
{
	skb->priority = _p2p_cfg80211_classify8021d(skb);

	return au16Wlan1dToQueueIdx[skb->priority];
}

static struct net_device *g_P2pPrDev;
static struct wireless_dev *gprP2pWdev;

/*----------------------------------------------------------------------------*/
/*!
* \brief A function for prDev->init
*
* \param[in] prDev      Pointer to struct net_device.
*
* \retval 0         The execution of wlanInit succeeds.
* \retval -ENXIO    No such device.
*/
/*----------------------------------------------------------------------------*/
static int p2pInit(struct net_device *prDev)
{
/* P_GLUE_INFO_T prGlueInfo; */
	if (!prDev)
		return -ENXIO;

	DBGLOG(P2P, INFO, "dev name=%s\n", prDev->name);
	return 0;		/* success */
}				/* end of p2pInit() */

/*----------------------------------------------------------------------------*/
/*!
* \brief A function for prDev->uninit
*
* \param[in] prDev      Pointer to struct net_device.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
static void p2pUninit(IN struct net_device *prDev)
{

}				/* end of p2pUninit() */

static const struct net_device_ops p2p_netdev_ops = {
	.ndo_open = p2pOpen,
	.ndo_stop = p2pStop,
	.ndo_set_mac_address = p2pSetMACAddress,
	.ndo_set_rx_mode = p2pSetMulticastList,
	.ndo_get_stats = p2pGetStats,
	.ndo_start_xmit = p2pHardStartXmit,
	.ndo_select_queue = p2pSelectQueue,
	.ndo_init = p2pInit,
	.ndo_uninit = p2pUninit,
};

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
* \brief Allocate memory for P2P_INFO, GL_P2P_INFO, P2P_CONNECTION_SETTINGS
*                                          P2P_SPECIFIC_BSS_INFO, P2P_FSM_INFO
*
* \param[in] prGlueInfo      Pointer to glue info
*
* \return   TRUE
*           FALSE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN p2PAllocInfo(IN P_GLUE_INFO_T prGlueInfo)
{
	P_ADAPTER_T prAdapter = NULL;
	P_WIFI_VAR_T prWifiVar = NULL;

	if ((!prGlueInfo) || (!prGlueInfo->prAdapter)) {
		ASSERT(FALSE);
		return FALSE;
	}

	prAdapter = prGlueInfo->prAdapter;
	prWifiVar = &(prAdapter->rWifiVar);

	if (!prWifiVar) {
		ASSERT(FALSE);
		return FALSE;
	}

	do {
		if (prGlueInfo->prP2PInfo == NULL) {
			/*alloc memory for p2p info */
			prGlueInfo->prP2PInfo = kalMemAlloc(sizeof(GL_P2P_INFO_T), VIR_MEM_TYPE);
			prAdapter->prP2pInfo = kalMemAlloc(sizeof(P2P_INFO_T), VIR_MEM_TYPE);
			prWifiVar->prP2PConnSettings = kalMemAlloc(sizeof(P2P_CONNECTION_SETTINGS_T), VIR_MEM_TYPE);
			prWifiVar->prP2pFsmInfo = kalMemAlloc(sizeof(P2P_FSM_INFO_T), VIR_MEM_TYPE);
			prWifiVar->prP2pSpecificBssInfo = kalMemAlloc(sizeof(P2P_SPECIFIC_BSS_INFO_T), VIR_MEM_TYPE);
		} else {
			ASSERT(prAdapter->prP2pInfo != NULL);
			ASSERT(prWifiVar->prP2PConnSettings != NULL);
			ASSERT(prWifiVar->prP2pFsmInfo != NULL);
			ASSERT(prWifiVar->prP2pSpecificBssInfo != NULL);
		}
		/*MUST set memory to 0 */
		if (prGlueInfo->prP2PInfo)
			kalMemZero(prGlueInfo->prP2PInfo, sizeof(GL_P2P_INFO_T));
		if (prAdapter->prP2pInfo)
			kalMemZero(prAdapter->prP2pInfo, sizeof(P2P_INFO_T));
		if (prWifiVar->prP2PConnSettings)
			kalMemZero(prWifiVar->prP2PConnSettings, sizeof(P2P_CONNECTION_SETTINGS_T));
		if (prWifiVar->prP2pFsmInfo)
			kalMemZero(prWifiVar->prP2pFsmInfo, sizeof(P2P_FSM_INFO_T));
		if (prWifiVar->prP2pSpecificBssInfo)
			kalMemZero(prWifiVar->prP2pSpecificBssInfo, sizeof(P2P_SPECIFIC_BSS_INFO_T));

	} while (FALSE);

	/* chk if alloc successful or not */
	if (prGlueInfo->prP2PInfo &&
	    prAdapter->prP2pInfo &&
	    prWifiVar->prP2PConnSettings && prWifiVar->prP2pFsmInfo && prWifiVar->prP2pSpecificBssInfo) {
		return TRUE;
	}

	if (prWifiVar->prP2pSpecificBssInfo) {
		kalMemFree(prWifiVar->prP2pSpecificBssInfo, VIR_MEM_TYPE, sizeof(P2P_SPECIFIC_BSS_INFO_T));

		prWifiVar->prP2pSpecificBssInfo = NULL;
	}
	if (prWifiVar->prP2pFsmInfo) {
		kalMemFree(prWifiVar->prP2pFsmInfo, VIR_MEM_TYPE, sizeof(P2P_FSM_INFO_T));

		prWifiVar->prP2pFsmInfo = NULL;
	}
	if (prWifiVar->prP2PConnSettings) {
		kalMemFree(prWifiVar->prP2PConnSettings, VIR_MEM_TYPE, sizeof(P2P_CONNECTION_SETTINGS_T));

		prWifiVar->prP2PConnSettings = NULL;
	}
	if (prGlueInfo->prP2PInfo) {
		kalMemFree(prGlueInfo->prP2PInfo, VIR_MEM_TYPE, sizeof(GL_P2P_INFO_T));

		prGlueInfo->prP2PInfo = NULL;
	}
	if (prAdapter->prP2pInfo) {
		kalMemFree(prAdapter->prP2pInfo, VIR_MEM_TYPE, sizeof(P2P_INFO_T));

		prAdapter->prP2pInfo = NULL;
	}
	return FALSE;

}

/*----------------------------------------------------------------------------*/
/*!
* \brief Free memory for P2P_INFO, GL_P2P_INFO, P2P_CONNECTION_SETTINGS
*                                          P2P_SPECIFIC_BSS_INFO, P2P_FSM_INFO
*
* \param[in] prGlueInfo      Pointer to glue info
*
* \return   TRUE
*           FALSE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN p2PFreeInfo(P_GLUE_INFO_T prGlueInfo)
{

	if ((!prGlueInfo) || (!prGlueInfo->prAdapter)) {
		ASSERT(FALSE);
		return FALSE;
	}

	/* free memory after p2p module is ALREADY unregistered */
	if (prGlueInfo->prAdapter->fgIsP2PRegistered == FALSE) {

		kalMemFree(prGlueInfo->prAdapter->prP2pInfo, VIR_MEM_TYPE, sizeof(P2P_INFO_T));
		kalMemFree(prGlueInfo->prP2PInfo, VIR_MEM_TYPE, sizeof(GL_P2P_INFO_T));
		kalMemFree(prGlueInfo->prAdapter->rWifiVar.prP2PConnSettings, VIR_MEM_TYPE,
			   sizeof(P2P_CONNECTION_SETTINGS_T));
		kalMemFree(prGlueInfo->prAdapter->rWifiVar.prP2pFsmInfo, VIR_MEM_TYPE, sizeof(P2P_FSM_INFO_T));
		kalMemFree(prGlueInfo->prAdapter->rWifiVar.prP2pSpecificBssInfo, VIR_MEM_TYPE,
			   sizeof(P2P_SPECIFIC_BSS_INFO_T));

		/*Reomve p2p bss scan list */
		scanRemoveAllP2pBssDesc(prGlueInfo->prAdapter);

		/*reset all pointer to NULL */
		prGlueInfo->prP2PInfo = NULL;
		prGlueInfo->prAdapter->prP2pInfo = NULL;
		prGlueInfo->prAdapter->rWifiVar.prP2PConnSettings = NULL;
		prGlueInfo->prAdapter->rWifiVar.prP2pFsmInfo = NULL;
		prGlueInfo->prAdapter->rWifiVar.prP2pSpecificBssInfo = NULL;

		return TRUE;
	} else {
		return FALSE;
	}

}

#if !CFG_SUPPORT_PERSIST_NETDEV
BOOLEAN p2pNetRegister(P_GLUE_INFO_T prGlueInfo, BOOLEAN fgIsRtnlLockAcquired)
{
	BOOLEAN fgDoRegister = FALSE;
/* BOOLEAN fgRollbackRtnlLock = FALSE; */
	BOOLEAN ret;

	GLUE_SPIN_LOCK_DECLARATION();

	if ((!prGlueInfo) || (!prGlueInfo->prAdapter)) {
		ASSERT(FALSE);
		return FALSE;
	}

	GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_NET_DEV);
	if (prGlueInfo->prAdapter->rP2PNetRegState == ENUM_NET_REG_STATE_UNREGISTERED) {
		prGlueInfo->prAdapter->rP2PNetRegState = ENUM_NET_REG_STATE_REGISTERING;
		fgDoRegister = TRUE;
	}
	GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_NET_DEV);

	if (!fgDoRegister)
		return TRUE;

	/* net device initialize */
	netif_carrier_off(prGlueInfo->prP2PInfo->prDevHandler);
	netif_tx_stop_all_queues(prGlueInfo->prP2PInfo->prDevHandler);

	/* register for net device */
	if (register_netdev(prGlueInfo->prP2PInfo->prDevHandler) < 0) {
		DBGLOG(P2P, WARN, "unable to register netdevice for p2p\n");

		free_netdev(prGlueInfo->prP2PInfo->prDevHandler);

		ret = FALSE;
	} else {
		prGlueInfo->prAdapter->rP2PNetRegState = ENUM_NET_REG_STATE_REGISTERED;
		ret = TRUE;
	}
	return ret;
}

BOOLEAN p2pNetUnregister(P_GLUE_INFO_T prGlueInfo, BOOLEAN fgIsRtnlLockAcquired)
{
	BOOLEAN fgDoUnregister = FALSE;
/* BOOLEAN fgRollbackRtnlLock = FALSE; */
	GLUE_SPIN_LOCK_DECLARATION();

	if ((!prGlueInfo) || (!prGlueInfo->prAdapter)) {
		ASSERT(FALSE);
		return FALSE;
	}

	GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_NET_DEV);
	if (prGlueInfo->prAdapter->rP2PNetRegState == ENUM_NET_REG_STATE_REGISTERED) {
		prGlueInfo->prAdapter->rP2PNetRegState = ENUM_NET_REG_STATE_UNREGISTERING;
		fgDoUnregister = TRUE;
	}
	GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_NET_DEV);

	if (!fgDoUnregister)
		return TRUE;

	/* prepare for removal */
	if (netif_carrier_ok(prGlueInfo->prP2PInfo->prDevHandler))
		netif_carrier_off(prGlueInfo->prP2PInfo->prDevHandler);

	netif_tx_stop_all_queues(prGlueInfo->prP2PInfo->prDevHandler);
	DBGLOG(P2P, INFO, "P2P unregister_netdev 0x%p\n", prGlueInfo->prP2PInfo->prDevHandler);
	unregister_netdev(prGlueInfo->prP2PInfo->prDevHandler);

	prGlueInfo->prAdapter->rP2PNetRegState = ENUM_NET_REG_STATE_UNREGISTERED;

	return TRUE;
}
#endif

BOOLEAN glP2pCreateWirelessDevice(P_GLUE_INFO_T prGlueInfo)
{
	struct wiphy *prWiphy = NULL;
	struct wireless_dev *prWdev = NULL;
#if CFG_SUPPORT_PERSIST_NETDEV
	struct net_device *prNetDev = NULL;
#endif
#if CFG_ENABLE_WIFI_DIRECT_CFG_80211
	prWdev = kzalloc(sizeof(struct wireless_dev), GFP_KERNEL);
	if (!prWdev) {
		DBGLOG(P2P, ERROR, "allocate p2p wireless device fail, no memory\n");
		return FALSE;
	}
	/* 1. allocate WIPHY */
	prWiphy = wiphy_new(&mtk_p2p_ops, sizeof(P_GLUE_INFO_T));
	if (!prWiphy) {
		DBGLOG(P2P, ERROR, "unable to allocate wiphy for p2p\n");
		goto free_wdev;
	}

	prWiphy->interface_modes = BIT(NL80211_IFTYPE_AP) | BIT(NL80211_IFTYPE_P2P_CLIENT) |
						BIT(NL80211_IFTYPE_P2P_GO) | BIT(NL80211_IFTYPE_STATION);

	prWiphy->bands[NL80211_BAND_2GHZ] = &mtk_band_2ghz;
	prWiphy->bands[NL80211_BAND_5GHZ] = &mtk_band_5ghz;

	prWiphy->mgmt_stypes = mtk_cfg80211_default_mgmt_stypes;
	prWiphy->max_remain_on_channel_duration = 5000;
	prWiphy->cipher_suites = mtk_cipher_suites;
	prWiphy->n_cipher_suites = ARRAY_SIZE(mtk_cipher_suites);
	prWiphy->flags = WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL | WIPHY_FLAG_HAVE_AP_SME;
	prWiphy->regulatory_flags = REGULATORY_CUSTOM_REG;
	prWiphy->ap_sme_capa = 1;

	prWiphy->max_scan_ssids = MAX_SCAN_LIST_NUM;
	prWiphy->max_scan_ie_len = MAX_SCAN_IE_LEN;
	prWiphy->signal_type = CFG80211_SIGNAL_TYPE_MBM;
	prWiphy->vendor_commands = mtk_p2p_vendor_ops;
	prWiphy->n_vendor_commands = sizeof(mtk_p2p_vendor_ops) / sizeof(struct wiphy_vendor_command);

#ifdef CONFIG_PM
	prWiphy->wowlan = &p2p_wowlan_support;
#endif

	/* 2.1 set priv as pointer to glue structure */
	*((P_GLUE_INFO_T *) wiphy_priv(prWiphy)) = prGlueInfo;
	 if (wiphy_register(prWiphy) < 0) {
		DBGLOG(P2P, ERROR, "fail to register wiphy for p2p\n");
		goto free_wiphy;
	 }
	prWdev->wiphy = prWiphy;
#if CFG_SUPPORT_PERSIST_NETDEV
	/* 3. allocate netdev */
	prNetDev = alloc_netdev_mq(sizeof(P_GLUE_INFO_T), P2P_MODE_INF_NAME, NET_NAME_PREDICTABLE,
								ether_setup, CFG_MAX_TXQ_NUM);
	if (!prNetDev) {
		DBGLOG(P2P, ERROR, "unable to allocate netdevice for p2p\n");
		goto unregister_wiphy;
	}

	/* 4. setup netdev */
	/* 4.1 Point to shared glue structure */
	*((P_GLUE_INFO_T *) netdev_priv(prNetDev)) = prGlueInfo;

	/* 4.2 fill hardware address */
	/* COPY_MAC_ADDR(rMacAddr, prAdapter->rMyMacAddr);
	rMacAddr[0] ^= 0x2; // change to local administrated address
	memcpy(prGlueInfo->prP2PInfo->prDevHandler->dev_addr, rMacAddr, ETH_ALEN);
	memcpy(prGlueInfo->prP2PInfo->prDevHandler->perm_addr,
			prGlueInfo->prP2PInfo->prDevHandler->dev_addr, ETH_ALEN);*/

	/* 4.3 register callback functions */
	prNetDev->netdev_ops = &p2p_netdev_ops;
	/* prGlueInfo->prP2PInfo->prDevHandler->wireless_handlers = &mtk_p2p_wext_handler_def;*/

	prNetDev->ieee80211_ptr = prWdev;
	prWdev->netdev = prNetDev;

#if CFG_TCP_IP_CHKSUM_OFFLOAD
	prNetDev->features = NETIF_F_IP_CSUM;
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */
	/* net device initialize */
	netif_carrier_off(prNetDev);
	netif_tx_stop_all_queues(prNetDev);

	/* register for net device */
	if (register_netdev(prNetDev) < 0) {
		DBGLOG(P2P, ERROR, "unable to register netdevice for p2p\n");
		free_netdev(prNetDev);
		goto unregister_wiphy;
	}
#endif
	gprP2pWdev = prWdev;
	return TRUE;

#if CFG_SUPPORT_PERSIST_NETDEV
unregister_wiphy:
	wiphy_unregister(prWiphy);
#endif
free_wiphy:
	wiphy_free(prWiphy);
free_wdev:
	kfree(prWdev);
#endif
	return FALSE;
}

void glP2pDestroyWirelessDevice(VOID)
{
#if CFG_ENABLE_WIFI_DIRECT_CFG_80211
#if CFG_SUPPORT_PERSIST_NETDEV
	unregister_netdev(gprP2pWdev->netdev);
	free_netdev(gprP2pWdev->netdev);
#endif
	wiphy_unregister(gprP2pWdev->wiphy);
	wiphy_free(gprP2pWdev->wiphy);
	kfree(gprP2pWdev);
	gprP2pWdev = NULL;
#endif
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Register for cfg80211 for Wi-Fi Direct
*
* \param[in] prGlueInfo      Pointer to glue info
*
* \return   TRUE
*           FALSE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN glRegisterP2P(P_GLUE_INFO_T prGlueInfo, const char *prDevName, BOOLEAN fgIsApMode)
{
	P_ADAPTER_T prAdapter = NULL;
	P_GL_HIF_INFO_T prHif = NULL;
	PARAM_MAC_ADDRESS rMacAddr;
	struct net_device *prDevHandler = NULL;
#if CFG_ENABLE_WIFI_DIRECT_CFG_80211
	struct device *prDev;
#endif

	ASSERT(prGlueInfo);

	prAdapter = prGlueInfo->prAdapter;
	ASSERT(prAdapter);

	prHif = &prGlueInfo->rHifInfo;
	ASSERT(prHif);

	DBGLOG(P2P, TRACE, "glRegisterP2P\n");
#if CFG_ENABLE_WIFI_DIRECT_CFG_80211
	if (!gprP2pWdev) {
		DBGLOG(P2P, ERROR, "gl_p2p, wireless device is not exist\n");
		return FALSE;
	}
#endif
	/*0. allocate p2pinfo */
	if (!p2PAllocInfo(prGlueInfo)) {
		DBGLOG(P2P, ERROR, "Allocate memory for p2p FAILED\n");
		ASSERT(0);
		return FALSE;
	}
#if CFG_ENABLE_WIFI_DIRECT_CFG_80211
	prGlueInfo->prP2PInfo->prWdev = gprP2pWdev;
	/* 1. fill wiphy parameters */
#if MTK_WCN_HIF_SDIO
	mtk_wcn_hif_sdio_get_dev(prHif->cltCtx, &prDev);
	if (!prDev)
		DBGLOG(P2P, WARN, "unable to get struct dev for p2p\n");
#else
	prDev = prHif->Dev;
#endif
	/*set_wiphy_dev(gprP2pWdev->wiphy, prDev);*/
	if (!prGlueInfo->prAdapter->fgEnable5GBand)
		gprP2pWdev->wiphy->bands[NL80211_BAND_5GHZ] = NULL;

	/* 2 set priv as pointer to glue structure */
	*(P_GLUE_INFO_T *) wiphy_priv(gprP2pWdev->wiphy) = prGlueInfo;

	if (fgIsApMode) {
		gprP2pWdev->iftype = NL80211_IFTYPE_AP;
#if CFG_SUPPORT_PERSIST_NETDEV
		if (kalStrnCmp(gprP2pWdev->netdev->name, AP_MODE_INF_NAME, 2)) {
			rtnl_lock();
			dev_change_name(gprP2pWdev->netdev->name, AP_MODE_INF_NAME);
			rtnl_unlock();
		}
#endif
	} else {
#if CFG_SUPPORT_PERSIST_NETDEV
		if (kalStrnCmp(gprP2pWdev->netdev->name, P2P_MODE_INF_NAME, 3)) {
			rtnl_lock();
			dev_change_name(gprP2pWdev->netdev->name, P2P_MODE_INF_NAME);
			rtnl_unlock();
		}
#endif
		gprP2pWdev->iftype = NL80211_IFTYPE_P2P_CLIENT;
	}
#endif /* CFG_ENABLE_WIFI_DIRECT_CFG_80211 */

#if CFG_SUPPORT_PERSIST_NETDEV
		prP2PInfo->prDevHandler = gprP2pWdev->netdev;
#else /* CFG_SUPPORT_PERSIST_NETDEV */
	/* 3. allocate netdev */
	prDevHandler =
	    alloc_netdev_mq(sizeof(P_GLUE_INFO_T), prDevName, NET_NAME_PREDICTABLE, ether_setup, CFG_MAX_TXQ_NUM);
	if (!prDevHandler) {
		DBGLOG(P2P, ERROR, "unable to allocate netdevice for p2p\n");
		return FALSE;
	}
	prGlueInfo->prP2PInfo->prDevHandler = prDevHandler;
	/* 4. setup netdev */
	/* 4.1 Point to shared glue structure */
	*((P_GLUE_INFO_T *) netdev_priv(prDevHandler)) = prGlueInfo;

	/* 4.2 fill hardware address */
	COPY_MAC_ADDR(rMacAddr, prAdapter->rMyMacAddr);
	rMacAddr[0] ^= 0x2;	/* change to local administrated address */
	eth_hw_addr_set(prDevHandler, rMacAddr);
	ether_addr_copy(prDevHandler->perm_addr, prDevHandler->dev_addr);

	/* 4.3 register callback functions */
	prDevHandler->netdev_ops = &p2p_netdev_ops;
	/* prGlueInfo->prP2PInfo->prDevHandler->wireless_handlers = &mtk_p2p_wext_handler_def; */

#if (MTK_WCN_HIF_SDIO == 0)
	SET_NETDEV_DEV(prDevHandler, prHif->Dev);
#endif

#if CFG_ENABLE_WIFI_DIRECT_CFG_80211
	prDevHandler->ieee80211_ptr = gprP2pWdev;
	gprP2pWdev->netdev = prDevHandler;
#endif

#if CFG_TCP_IP_CHKSUM_OFFLOAD
	prDevHandler->features = NETIF_F_IP_CSUM;
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */
#endif /* CFG_SUPPORT_PERSIST_NETDEV */

	/* 5. set p2p net device register state */
	prAdapter->rP2PNetRegState = ENUM_NET_REG_STATE_UNREGISTERED;

	/* 6. setup running mode */
	prAdapter->rWifiVar.prP2pFsmInfo->fgIsApMode = fgIsApMode;

	/* 7. finish */
	p2pFsmInit(prAdapter);

	p2pFuncInitConnectionSettings(prAdapter, prAdapter->rWifiVar.prP2PConnSettings);

	/* Active network too early would cause HW not able to sleep.
	 * Defer the network active time.
	 */
/* nicActivateNetwork(prAdapter, NETWORK_TYPE_P2P_INDEX); */

	return TRUE;
}				/* end of glRegisterP2P() */

/*----------------------------------------------------------------------------*/
/*!
* \brief Unregister Net Device for Wi-Fi Direct
*
* \param[in] prGlueInfo      Pointer to glue info
*
* \return   TRUE
*           FALSE
*/
/*----------------------------------------------------------------------------*/
BOOLEAN glUnregisterP2P(P_GLUE_INFO_T prGlueInfo)
{
	ASSERT(prGlueInfo);
	/* normal flow: this func will called first before wlanRemove, and it can do fsmUninit/deactivateNetwork
	gracefully. */
	/* when reset: because tx_thread with fw has stopped, so it can't do these job and the recovery will be
	dependent on chip system reset. */
	/* if so, just skip it by flag GLUE_FLAG_HALT(warning: when tx_thread was stop, this flag was not cleared,
	and NEED TO KEEP IT NOT CLEARED!). */
	if (!(prGlueInfo->ulFlag & GLUE_FLAG_HALT)) {
		p2pFsmUninit(prGlueInfo->prAdapter);
		nicDeactivateNetwork(prGlueInfo->prAdapter, NETWORK_TYPE_P2P_INDEX);
	}
#if CFG_SUPPORT_PERSIST_NETDEV
	dev_close(prGlueInfo->prP2PInfo->prDevHandler);
#else
	free_netdev(prGlueInfo->prP2PInfo->prDevHandler);
	prGlueInfo->prP2PInfo->prDevHandler = NULL;
#endif
	/* Free p2p memory */
	if (!p2PFreeInfo(prGlueInfo)) {
		DBGLOG(P2P, ERROR, "Free memory for p2p FAILED\n");
		ASSERT(0);
		return FALSE;
	}
	return TRUE;
}				/* end of glUnregisterP2P() */

/*----------------------------------------------------------------------------*/
/*!
 * \brief A function for stop p2p fsm immediate
 *
 * \param[in] prGlueInfo      Pointer to struct P_GLUE_INFO_T.
 *
 * \retval TRUE     The execution succeeds.
 * \retval FALSE   The execution failed.
 */
/*----------------------------------------------------------------------------*/
BOOLEAN p2pStopImmediate(P_GLUE_INFO_T prGlueInfo)
{
/* P_ADAPTER_T prAdapter = NULL; */
/* P_MSG_P2P_FUNCTION_SWITCH_T prFuncSwitch; */

	ASSERT(prGlueInfo);

/* prAdapter = prGlueInfo->prAdapter; */
/* ASSERT(prAdapter); */

	/* 1. stop TX queue */
	netif_tx_stop_all_queues(prGlueInfo->prP2PInfo->prDevHandler);

#if 0
	/* 2. switch P2P-FSM off */
	/* 2.1 allocate for message */
	prFuncSwitch = (P_MSG_P2P_FUNCTION_SWITCH_T) cnmMemAlloc(prAdapter,
								 RAM_TYPE_MSG, sizeof(MSG_P2P_FUNCTION_SWITCH_T));

	if (!prFuncSwitch) {
		ASSERT(0);	/* Can't trigger P2P FSM */
		DBGLOG(P2P, ERROR, "Allocate for p2p mesasage FAILED\n");
		/* return -ENOMEM; */
	}

	/* 2.2 fill message */
	prFuncSwitch->rMsgHdr.eMsgId = MID_MNY_P2P_FUN_SWITCH;
	prFuncSwitch->fgIsFuncOn = FALSE;

	/* 2.3 send message */
	mboxSendMsg(prAdapter, MBOX_ID_0, (P_MSG_HDR_T) prFuncSwitch, MSG_SEND_METHOD_UNBUF);

#endif

	/* 3. stop queue and turn off carrier */
	prGlueInfo->prP2PInfo->eState = PARAM_MEDIA_STATE_DISCONNECTED;

	return TRUE;
}				/* end of p2pStop() */

/* Net Device Hooks */
/*----------------------------------------------------------------------------*/
/*!
 * \brief A function for net_device open (ifup)
 *
 * \param[in] prDev      Pointer to struct net_device.
 *
 * \retval 0     The execution succeeds.
 * \retval < 0   The execution failed.
 */
/*----------------------------------------------------------------------------*/
static int p2pOpen(IN struct net_device *prDev)
{
/* P_GLUE_INFO_T prGlueInfo = NULL; */
/* P_ADAPTER_T prAdapter = NULL; */
/* P_MSG_P2P_FUNCTION_SWITCH_T prFuncSwitch; */

	ASSERT(prDev);

#if 0				/* Move after device name set. (mtk_p2p_set_local_dev_info) */
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prDev));
	ASSERT(prGlueInfo);

	prAdapter = prGlueInfo->prAdapter;
	ASSERT(prAdapter);

	/* 1. switch P2P-FSM on */
	/* 1.1 allocate for message */
	prFuncSwitch = (P_MSG_P2P_FUNCTION_SWITCH_T) cnmMemAlloc(prAdapter,
								 RAM_TYPE_MSG, sizeof(MSG_P2P_FUNCTION_SWITCH_T));

	if (!prFuncSwitch) {
		ASSERT(0);	/* Can't trigger P2P FSM */
		return -ENOMEM;
	}

	/* 1.2 fill message */
	prFuncSwitch->rMsgHdr.eMsgId = MID_MNY_P2P_FUN_SWITCH;
	prFuncSwitch->fgIsFuncOn = TRUE;

	/* 1.3 send message */
	mboxSendMsg(prAdapter, MBOX_ID_0, (P_MSG_HDR_T) prFuncSwitch, MSG_SEND_METHOD_BUF);
#endif

	/* 2. carrier on & start TX queue */
	netif_carrier_on(prDev);
	netif_tx_start_all_queues(prDev);

	return 0;		/* success */
}				/* end of p2pOpen() */

/*----------------------------------------------------------------------------*/
/*!
 * \brief A function for net_device stop (ifdown)
 *
 * \param[in] prDev      Pointer to struct net_device.
 *
 * \retval 0     The execution succeeds.
 * \retval < 0   The execution failed.
 */
/*----------------------------------------------------------------------------*/
static int p2pStop(IN struct net_device *prDev)
{
	P_GLUE_INFO_T prGlueInfo = NULL;
	/* P_ADAPTER_T prAdapter = NULL; */
/* P_MSG_P2P_FUNCTION_SWITCH_T prFuncSwitch; */
	P_GL_P2P_INFO_T prGlueP2pInfo = (P_GL_P2P_INFO_T) NULL;

        struct cfg80211_scan_info info = {
               .aborted = true,
        };

	struct cfg80211_scan_request *prScanRequest = NULL;

	GLUE_SPIN_LOCK_DECLARATION();
	ASSERT(prDev);

	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prDev));
	ASSERT(prGlueInfo);

	prGlueP2pInfo = prGlueInfo->prP2PInfo;
	ASSERT(prGlueP2pInfo);

	/* CFG80211 down */
	GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_NET_DEV);
	if (prGlueP2pInfo->prScanRequest != NULL) {
		prScanRequest = prGlueP2pInfo->prScanRequest;
		prGlueP2pInfo->prScanRequest = NULL;
	}
	GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_NET_DEV);

	if (prScanRequest)
		cfg80211_scan_done(prScanRequest, &info);
#if 0

	/* 1. stop TX queue */
	netif_tx_stop_all_queues(prDev);

	/* 2. switch P2P-FSM off */
	/* 2.1 allocate for message */
	prFuncSwitch = (P_MSG_P2P_FUNCTION_SWITCH_T) cnmMemAlloc(prAdapter,
								 RAM_TYPE_MSG, sizeof(MSG_P2P_FUNCTION_SWITCH_T));

	if (!prFuncSwitch) {
		ASSERT(0);	/* Can't trigger P2P FSM */
		return -ENOMEM;
	}

	/* 2.2 fill message */
	prFuncSwitch->rMsgHdr.eMsgId = MID_MNY_P2P_FUN_SWITCH;
	prFuncSwitch->fgIsFuncOn = FALSE;

	/* 2.3 send message */
	mboxSendMsg(prAdapter, MBOX_ID_0, (P_MSG_HDR_T) prFuncSwitch, MSG_SEND_METHOD_BUF);
#endif
	/* 3. stop queue and turn off carrier */
	prGlueInfo->prP2PInfo->eState = PARAM_MEDIA_STATE_DISCONNECTED;

	netif_tx_stop_all_queues(prDev);
	if (netif_carrier_ok(prDev))
		netif_carrier_off(prDev);

	return 0;
}				/* end of p2pStop() */

/*----------------------------------------------------------------------------*/
/*!
 * \brief A method of struct net_device, to get the network interface statistical
 *        information.
 *
 * Whenever an application needs to get statistics for the interface, this method
 * is called. This happens, for example, when ifconfig or netstat -i is run.
 *
 * \param[in] prDev      Pointer to struct net_device.
 *
 * \return net_device_stats buffer pointer.
 */
/*----------------------------------------------------------------------------*/
struct net_device_stats *p2pGetStats(IN struct net_device *prDev)
{
	P_GLUE_INFO_T prGlueInfo = NULL;

	ASSERT(prDev);

	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prDev));

#if CFG_SUPPORT_PERSIST_NETDEV
	/* @FIXME */
	/* prDev->stats.rx_packets = 0; */
	/* prDev->stats.tx_packets = 0; */
	prDev->stats.tx_errors = 0;
	prDev->stats.rx_errors = 0;
	/* prDev->stats.rx_bytes = 0; */
	/* prDev->stats.tx_bytes = 0; */
	prDev->stats.multicast = 0;

	return &prDev->stats;

#else
	/* prGlueInfo->prP2PInfo->rNetDevStats.rx_packets = 0; */
	/* prGlueInfo->prP2PInfo->rNetDevStats.tx_packets = 0; */
	prGlueInfo->prP2PInfo->rNetDevStats.tx_errors = 0;
	prGlueInfo->prP2PInfo->rNetDevStats.rx_errors = 0;
	/* prGlueInfo->prP2PInfo->rNetDevStats.rx_bytes   = 0; */
	/* prGlueInfo->prP2PInfo->rNetDevStats.tx_bytes   = 0; */
	/* prGlueInfo->prP2PInfo->rNetDevStats.rx_errors  = 0; */
	prGlueInfo->prP2PInfo->rNetDevStats.multicast = 0;

	return &prGlueInfo->prP2PInfo->rNetDevStats;
#endif
}				/* end of p2pGetStats() */

static void p2pSetMulticastList(IN struct net_device *prDev)
{
	P_GLUE_INFO_T prGlueInfo = (P_GLUE_INFO_T) NULL;

	prGlueInfo = (NULL != prDev) ? *((P_GLUE_INFO_T *) netdev_priv(prDev)) : NULL;

	ASSERT(prDev);
	ASSERT(prGlueInfo);
	if (!prDev || !prGlueInfo) {
		DBGLOG(P2P, WARN, "abnormal dev or skb: prDev(0x%p), prGlueInfo(0x%p)\n", prDev, prGlueInfo);
		return;
	}

	g_P2pPrDev = prDev;

	/* 4  Mark HALT, notify main thread to finish current job */
/* prGlueInfo->u4Flag |= GLUE_FLAG_SUB_MOD_MULTICAST; */
	set_bit(GLUE_FLAG_SUB_MOD_MULTICAST_BIT, &prGlueInfo->ulFlag);

	/* wake up main thread */
	wake_up_interruptible(&prGlueInfo->waitq);

}				/* p2pSetMulticastList */

/* FIXME: Since we cannot sleep in the wlanSetMulticastList, we arrange
 * another workqueue for sleeping. We don't want to block
 * tx_thread, so we can't let tx_thread to do this */

void p2pSetMulticastListWorkQueueWrapper(P_GLUE_INFO_T prGlueInfo)
{
	if (!prGlueInfo) {
		DBGLOG(INIT, ERROR, "prGlueInfo is NULL\n");
		return;
	}
#if CFG_ENABLE_WIFI_DIRECT
	if (prGlueInfo->prAdapter->fgIsP2PRegistered)
		mtk_p2p_wext_set_Multicastlist(prGlueInfo);
#endif
}				/* end of p2pSetMulticastListWorkQueueWrapper() */

/*----------------------------------------------------------------------------*/
/*!
 * \brief This function is to set multicast list and set rx mode.
 *
 * \param[in] prDev  Pointer to struct net_device
 *
 * \return (none)
 */
/*----------------------------------------------------------------------------*/
void mtk_p2p_wext_set_Multicastlist(P_GLUE_INFO_T prGlueInfo)
{
	UINT_32 u4SetInfoLen = 0;
	struct net_device *prDev = g_P2pPrDev;

	prGlueInfo = (NULL != prDev) ? *((P_GLUE_INFO_T *) netdev_priv(prDev)) : NULL;

	ASSERT(prDev);
	ASSERT(prGlueInfo);
	if (!prDev || !prGlueInfo) {
		DBGLOG(P2P, WARN, "abnormal dev or skb: prDev(0x%p), prGlueInfo(0x%p)\n", prDev, prGlueInfo);
		return;
	}

	if (prDev->flags & IFF_PROMISC)
		prGlueInfo->prP2PInfo->u4PacketFilter |= PARAM_PACKET_FILTER_PROMISCUOUS;

	if (prDev->flags & IFF_BROADCAST)
		prGlueInfo->prP2PInfo->u4PacketFilter |= PARAM_PACKET_FILTER_BROADCAST;

	if (prDev->flags & IFF_MULTICAST) {
		if ((prDev->flags & IFF_ALLMULTI) ||
		    (netdev_mc_count(prDev) > MAX_NUM_GROUP_ADDR)) {
			prGlueInfo->prP2PInfo->u4PacketFilter |= PARAM_PACKET_FILTER_ALL_MULTICAST;
		} else {
			prGlueInfo->prP2PInfo->u4PacketFilter |= PARAM_PACKET_FILTER_MULTICAST;
		}
	}

	if (prGlueInfo->prP2PInfo->u4PacketFilter & PARAM_PACKET_FILTER_MULTICAST) {
		/* Prepare multicast address list */
		struct netdev_hw_addr *ha;
		UINT_32 i = 0;

		netdev_for_each_mc_addr(ha, prDev) {
			if (i < MAX_NUM_GROUP_ADDR) {
				COPY_MAC_ADDR(&(prGlueInfo->prP2PInfo->aucMCAddrList[i]), ha->addr);
				i++;
			}
		}

		DBGLOG(P2P, TRACE, "SEt Multicast Address List\n");

		if (i >= MAX_NUM_GROUP_ADDR)
			return;
		wlanoidSetP2PMulticastList(prGlueInfo->prAdapter,
					   &(prGlueInfo->prP2PInfo->aucMCAddrList[0]), (i * ETH_ALEN), &u4SetInfoLen);

	}

}				/* end of mtk_p2p_wext_set_Multicastlist */

/*----------------------------------------------------------------------------*/
/*!
 * * \brief This function is TX entry point of NET DEVICE.
 * *
 * * \param[in] prSkb  Pointer of the sk_buff to be sent
 * * \param[in] prDev  Pointer to struct net_device
 * *
 * * \retval NETDEV_TX_OK - on success.
 * * \retval NETDEV_TX_BUSY - on failure, packet will be discarded by upper layer.
 * */
/*----------------------------------------------------------------------------*/
int p2pHardStartXmit(IN struct sk_buff *prSkb, IN struct net_device *prDev)
{
	P_QUE_ENTRY_T prQueueEntry = NULL;
	P_QUE_T prTxQueue = NULL;
	P_GLUE_INFO_T prGlueInfo = NULL;
	UINT_16 u2QueueIdx = 0;

	GLUE_SPIN_LOCK_DECLARATION();

	ASSERT(prSkb);
	ASSERT(prDev);

	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prDev));
	prGlueInfo->u8SkbToDriver++;

	if (prGlueInfo->ulFlag & GLUE_FLAG_HALT) {
		DBGLOG(P2P, ERROR, "GLUE_FLAG_HALT skip tx\n");
		prGlueInfo->u8SkbFreed++;
		dev_kfree_skb(prSkb);
		return NETDEV_TX_OK;
	}
#if (CFG_SUPPORT_MET_PROFILING == 1)
	kalMetProfilingStart(prGlueInfo, prSkb);
#endif

	/* mark as P2P packets */
	GLUE_SET_PKT_FLAG_P2P(prSkb);
#if CFG_ENABLE_PKT_LIFETIME_PROFILE
	GLUE_SET_PKT_ARRIVAL_TIME(prSkb, kalGetTimeTick());
#endif

	STATS_TX_TIME_ARRIVE(prSkb);
	prQueueEntry = (P_QUE_ENTRY_T) GLUE_GET_PKT_QUEUE_ENTRY(prSkb);
	prTxQueue = &prGlueInfo->rTxQueue;

	if (wlanProcessSecurityFrame(prGlueInfo->prAdapter, (P_NATIVE_PACKET) prSkb) == FALSE) {

		u2QueueIdx = skb_get_queue_mapping(prSkb);
		ASSERT(u2QueueIdx < CFG_MAX_TXQ_NUM);

		if (u2QueueIdx >= CFG_MAX_TXQ_NUM) {
			DBGLOG(P2P, ERROR, "Incorrect queue index, skip this frame\n");
			prGlueInfo->u8SkbFreed++;
			dev_kfree_skb(prSkb);
			return NETDEV_TX_OK;
		}
		GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_TX_QUE);
		QUEUE_INSERT_TAIL(prTxQueue, prQueueEntry);
		GLUE_RELEASE_SPIN_LOCK(prGlueInfo, SPIN_LOCK_TX_QUE);

		GLUE_INC_REF_CNT(prGlueInfo->i4TxPendingFrameNum);
		GLUE_INC_REF_CNT(prGlueInfo->ai4TxPendingFrameNumPerQueue[NETWORK_TYPE_P2P_INDEX][u2QueueIdx]);

		if (prGlueInfo->ai4TxPendingFrameNumPerQueue[NETWORK_TYPE_P2P_INDEX][u2QueueIdx] >=
		    CFG_TX_STOP_NETIF_PER_QUEUE_THRESHOLD) {
			DBGLOG(TX, INFO, "netif_stop_subqueue for p2p0, Queue len: %d\n",
				prGlueInfo->ai4TxPendingFrameNumPerQueue[NETWORK_TYPE_P2P_INDEX][u2QueueIdx]);
			netif_stop_subqueue(prDev, u2QueueIdx);
		}
	} else {
		GLUE_INC_REF_CNT(prGlueInfo->i4TxPendingSecurityFrameNum);
	}

	kalSetEvent(prGlueInfo);

	/* Statistic usage. */
	prGlueInfo->prP2PInfo->rNetDevStats.tx_bytes += prSkb->len;
	prGlueInfo->prP2PInfo->rNetDevStats.tx_packets++;
	/* prDev->stats.tx_packets++; */
	kalPerMonStart(prGlueInfo);
	return NETDEV_TX_OK;
}				/* end of p2pHardStartXmit() */

/*----------------------------------------------------------------------------*/
/*!
 * \brief To override p2p interface address
 *
 * \param[in] prDev Net device requested.
 * \param[in] addr  Pointer to address
 *
 * \retval 0 For success.
 * \retval -E2BIG For user's buffer size is too small.
 * \retval -EFAULT For fail.
 *
 */
/*----------------------------------------------------------------------------*/
int p2pSetMACAddress(IN struct net_device *prDev, void *addr)
{
	P_ADAPTER_T prAdapter = NULL;
	P_GLUE_INFO_T prGlueInfo = NULL;

	ASSERT(prDev);

	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prDev));
	ASSERT(prGlueInfo);

	prAdapter = prGlueInfo->prAdapter;
	ASSERT(prAdapter);

	/* @FIXME */
	return eth_mac_addr(prDev, addr);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief indicate an event to supplicant for device found
*
* \param[in] prGlueInfo Pointer of GLUE_INFO_T
*
* \retval TRUE  Success.
* \retval FALSE Failure
*/
/*----------------------------------------------------------------------------*/
BOOLEAN kalP2PIndicateFound(IN P_GLUE_INFO_T prGlueInfo)
{
	union iwreq_data evt;
	UINT_8 aucBuffer[IW_CUSTOM_MAX];

	ASSERT(prGlueInfo);

	memset(&evt, 0, sizeof(evt));

	snprintf(aucBuffer, IW_CUSTOM_MAX - 1, "P2P_DVC_FND");
	evt.data.length = strlen(aucBuffer);

	/* indicate IWEVP2PDVCFND event */
#ifdef CONFIG_WIRELESS_EXT
	wireless_send_event(prGlueInfo->prP2PInfo->prDevHandler, IWEVCUSTOM, &evt, aucBuffer);
#endif

	return FALSE;
}				/* end of kalP2PIndicateFound() */

