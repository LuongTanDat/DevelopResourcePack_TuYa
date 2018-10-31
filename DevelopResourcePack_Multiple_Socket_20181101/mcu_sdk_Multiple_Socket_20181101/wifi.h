/****************************************Copyright (c)*************************
**                               Copyright (C), 2015-2020, Tuya Technology
**
**                                 http://www.tuya.com
**
**--------------File information-------------------------------------------------------
**File name: wifi.h
**Description: Wifi file header definitio
**Instructions : The user don't need to care about the content
**
**
**--------------Current version corrections---------------------------------------------------
** Version: v2.3.7
** Date: 2017-4-18
** Description: 1:Improved the receiving and processing of serial port queue
		   
** Version: v2.3.6
** Date: 2016-7-21
** Description: 1:Corrected the failure to obtain local time
           2:Added hex_to_bcd transfer function
		   
** Version: v2.3.5
** Date: 2016-6-3
** Description: 1:The modified return protocol version is 0x01
           2:The firmware upgrade data offset is modified to 4 bytes

** Version: v2.3.4
** Date: 2016гн5гн26
** Description: 1:Improved the analytic function of serial port
           2:Improved the compatibility of compiler and cancleed enum category definition

** Version: v2.3.3
** Date: 2016-5-24
** Description: 1:Changed the functions that MCU obtain local time
           2:Added Wi-Fi function test

** Version: v2.3.2
** Date: 2016-4-23
** Description: 1:Improved analytics of serial data
           2:Improved MCU frmware update process
           3:Improved data reporting process

** Version: v2.3.1
** Date: 2016гн4гн15
** Description: 1:Improved analysis of serial data

** Version: v2.3
** Date: 2016-4-14
** Description: 1:Support MCU firmware online upgrade

** Version: v2.2
** Date: 2016-4-11-
** Description: 1:Changed the receiving way of serial data

** Version: v2.1
** Date: 2016-4-8
** Description: 1:Added the compatibility options, as some compilers don't support Function pointer

** Version: v2.0
** Date: 2016-3-29
** Description: 1:Improved code strcuture
2:Saved RAM space
**
**-----------------------------------------------------------------------------
******************************************************************************/
#ifndef __WIFI_H_
#define __WIFI_H_


//=============================================================================
/*Define constants*/
//=============================================================================
#ifndef TRUE
#define         TRUE                1
#endif
//
#ifndef FALSE
#define         FALSE               0
#endif
//
#ifndef NULL
#define         NULL                ((void *) 0)
#endif

#ifndef SUCCESS
#define         SUCCESS             1
#endif

#ifndef ERROR
#define         ERROR               0
#endif

#ifndef INVALID
#define         INVALID             0xFF
#endif

#ifndef ENABLE
#define         ENABLE                1
#endif
//
#ifndef DISABLE
#define         DISABLE               0
#endif
//=============================================================================
//dp data point type
//=============================================================================
#define         DP_TYPE_RAW                     0x00				//RAW type
#define         DP_TYPE_BOOL                    0x01	                        //Boolean type
#define         DP_TYPE_VALUE                   0x02	                        //Numeric type
#define         DP_TYPE_STRING                  0x03				//String type
#define         DP_TYPE_ENUM                    0x04				//Enumerated type
#define         DP_TYPE_FAULT                   0x05				//Fault type

//=============================================================================
//WIFI working status
//=============================================================================
#define         SMART_CONFIG_STATE              0x00
#define         AP_STATE                        0x01
#define         WIFI_NOT_CONNECTED              0x02
#define         WIFI_CONNECTED                  0x03
#define         WIFI_SATE_UNKNOW                0xff
//=============================================================================
//wifi consiguration method
//=============================================================================
#define         SMART_CONFIG                    0x0  
#define         AP_CONFIG                       0x1   

//=============================================================================
//wifi reset status
//=============================================================================
#define         RESET_WIFI_ERROR                0
#define         RESET_WIFI_SUCCESS              1

//=============================================================================
//wifi reset status
//=============================================================================
#define         SET_WIFICONFIG_ERROR            0
#define         SET_WIFICONFIG_SUCCESS          1

//=============================================================================
//MCU firmware upgrade status
//=============================================================================
#define         FIRM_STATE_UN_SUPPORT           0x00                            //Not support MCU upgrade
#define         FIRM_STATE_WIFI_UN_READY        0x01                            //The module is not ready
#define         FIRM_STATE_GET_ERROR            0x02                            //Failed to query the cloud upgrade information
#define         FIRM_STATE_NO                   0x03                            //No upgrade required (no update in the cloud)
#define         FIRM_STATE_START                0x04                            //Need to upgrade, wait for the module to initiate an upgrade action

//=============================================================================
//Working methods of Wifi and MCU
//=============================================================================
#define         UNION_WORK                      0x0                             //MCU module and Wifi work together
#define         WIFI_ALONE                      0x1                             //Wifi module self processing

//=============================================================================
//System working mode
//=============================================================================
#define         NORMAL_MODE             0x00                                    //Normal working status
#define         FACTORY_MODE            0x01                                    //Manufacture mode	
#define         UPDATE_MODE             0X02                                    //Uograde mode     

#include "protocol.h"
#include "system.h"
#include "mcu_api.h"


//=============================================================================
//Issued command
//=============================================================================
typedef struct {
  unsigned char dp_id;                        //dp serial number
  unsigned char dp_type;                          //dp type
} DOWNLOAD_CMD_S;

#endif