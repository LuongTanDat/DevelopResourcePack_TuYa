/****************************************Copyright (c)*************************
**                             Copyright (C), 2015-2020, Tuya Technology
**
**                                 http://www.tuya.com
**
**--------------File information-------------------------------------------------------
**File name: protocol.h
**Description: Issued/reported data processing function
**Instructions :

                  *******Important, must read !!********

** 1、The user implements the data issuing / reporting function in this file
** 2、DP ID / TYPE and data processing functions need to be implemented by the user according to the actual definition
** 3、When you start some macro definition, the user needs to implement the #err prompt inside code function. After function is compeleted, please delete the #err
**
**--------------Current version corrections---------------------------------------------------
** Version: v2.3.7
** Date: 2017－4－18
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
** Date: 2016－5－26
** Description: 1:Improved the analytic function of serial port
           2:Improved the compatibility of compiler and cancleed enum category definition

** Version: v2.3.3
** Date: 2016-5-24
** Description: 1:Changed the functions that MCU obtain local time
           2:Added Wi-Fi function test

* Version: v2.3.2
** Date: 2016-4-23
** Description: 1:Improved analytics of serial data
           2:Improved MCU frmware update process
           3:Improved data reporting process

** Version: v2.3.1
** Date: 2016－4－15
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
#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_



/******************************************************************************
                            User related information configuration
******************************************************************************/
/******************************************************************************
                            1:Change product information               
******************************************************************************/
#define PRODUCT_KEY "bhvdmzhfa9bnnft1"    //The unique product identification generated after product is created on development platform

#define MCU_VER "1.0.0"                                 //The user's software version is for MCU firmware upgrade. MCU uograde version needs to be changed. 
/******************************************************************************
                          2:Whether the MCU needs firmware upgrade                  
If you need to support the MCU firmware upgrade, please turn on the macro
The MCU can call the mcu_firm_update_query () function in the mcu_api.c file to get the current MCU firmware update information                        ********WARNING!!!**********
The current receive buffer is the size of the firmware update feature, and the firmware upgrade package is 256 bytes
If you need to enable this function, the serial receive buffer will become larger
******************************************************************************/
//#define         SUPPORT_MCU_FIRM_UPDATE                 //Enable MCU firmware upgrade (default off)
/******************************************************************************
                         3:Define send and receive cache:
                  If the current use of MCU RAM is not enough, can be modified to 24
******************************************************************************/
#ifndef SUPPORT_MCU_FIRM_UPDATE
#define WIFI_UART_QUEUE_LMT             16              ///Data reception queue size, such as MCU RAM is not enough, can be reduced
#define WIFI_UART_RECV_BUF_LMT          24              //Measured according to user DP data size, must greater than 24
#else
#define WIFI_UART_QUEUE_LMT             128             //Data reception queue size, such as MCU RAM is not enough, can be reduced
#define WIFI_UART_RECV_BUF_LMT          300             //Firmware upgrade buffer, need large cache, must be greater than 260
#endif

#define WIFIR_UART_SEND_BUF_LMT         24              //Measured according to user DP data size, must greater than 24
/******************************************************************************
                        4:Define how modules work
Module self processing:
          Wifi indicator and wifi reset button connected to the wifi module(Open the WIFI_CONTROL_SELF_MODE macro)
          And correctly define WF_STATE_KEY and WF_RESET_KEY
MCU self processing:
          Wifi indicator and wifi reset button connected to the MCU(Close WIFI_CONTROL_SELF_MODE macro)
          MCU calls the mcu_reset_wifi () function in the mcu_api.c file where the WiFi needs to be reset, and calls the mcu_get_reset_wifi_flag () function to return the reset WiFi result
          Or call the mcu_set_wifi_mode (WIFI_CONFIG_E, mode) function inside the WiFi schema mcu_api.c file and call the mcu_get_wifi_work_state () function to return the WiFi result
******************************************************************************/
//#define         WIFI_CONTROL_SELF_MODE                       //Wifi self-processing keys and LED indicators; If it is MCU external button/LED indicators, please close the macro
#ifdef          WIFI_CONTROL_SELF_MODE                      //Module self processing
  #define     WF_STATE_KEY            14                    //Wifi module status indicator button, set according to the actual GPIO pin
  #define     WF_RESERT_KEY           0                     //Wifi module reset button, please set according to the actual GPIO pin
#endif

/******************************************************************************
                      5:Does the MCU need to support the calibration time function                
If necessary, please open the macro and implement the code in the mcu_write_rtctime of Protocol.c file
There is #err inside mcu_write_rtctime, after function is completed, please delete the #err
MCU could call mcu_get_system_time() function after wifi module is correctly connected to start calibration time function 
******************************************************************************/
//#define         SUPPORT_MCU_RTC_CHECK                //Enable the calibration time function

/******************************************************************************
                      6:Whether the MCU needs to support the wifi function test
If necessary, please open the macro. MCU calls mcu_start_wifitest of mcu_api.c file in where wifi function test is needed  
And view the test result in the wifi_test_result function of protocol.c file,
#err prompt inside wifi_test_result, after function is completed, please delete the #err
******************************************************************************/
#define         WIFI_TEST_ENABLE                //Enable the WIFI production test function

/******************************************************************************
                        1:Redefine dp data point serial number
          **This is automatically generated code, if there are changes in the developer platform, please re-download MCU_SDK**         
******************************************************************************/
//Switch 1(可下发可上报)
//Notes:
#define DPID_SWITCH_1 1
//Switch 2(可下发可上报)
//Notes:
#define DPID_SWITCH_2 2
//Switch 3(可下发可上报)
//Notes:
#define DPID_SWITCH_3 3
//Switch 4(可下发可上报)
//Notes:
#define DPID_SWITCH_4 4
//Switch 5(可下发可上报)
//Notes:
#define DPID_SWITCH_5 5
//Switch 6(可下发可上报)
//Notes:
#define DPID_SWITCH_6 6
//Switch 7(可下发可上报)
//Notes:
#define DPID_SWITCH_USB1 7
//Switch 8(可下发可上报)
//Notes:
#define DPID_SWITCH_USB2 8
//Countdown 1(可下发可上报)
//Notes:
#define DPID_COUNTDOWN_1 9
//Countdown 2(可下发可上报)
//Notes:
#define DPID_COUNTDOWN_2 10
//Countdown 3(可下发可上报)
//Notes:
#define DPID_COUNTDOWN_3 11
//Countdown 4(可下发可上报)
//Notes:
#define DPID_COUNTDOWN_4 12
//Countdown 5(可下发可上报)
//Notes:
#define DPID_COUNTDOWN_5 13
//Countdown 6(可下发可上报)
//Notes:
#define DPID_COUNTDOWN_6 14
//Countdown 7(可下发可上报)
//Notes:
#define DPID_COUNTDOWN_USB1 15
//Countdown 8(可下发可上报)
//Notes:
#define DPID_COUNTDOWN_USB2 16
//Add Electricity(可下发可上报)
//Notes:
#define DPID_ADD_ELE 17
//Current(只上报)
//Notes:
#define DPID_CUR_CURRENT 18
//Power(只上报)
//Notes:
#define DPID_CUR_POWER 19
//Voltage(只上报)
//Notes:
#define DPID_CUR_VOLTAGE 20
//Test Bit(只上报)
//Notes:
#define DPID_TEST_BIT 21
//电压校准系数(只上报)
//Notes:
#define DPID_VOLTAGE_COE 22
//电流校准系数(只上报)
//Notes:
#define DPID_ELECTRIC_COE 23
//功率校准系数(只上报)
//Notes:
#define DPID_POWER_COE 24
//电量校准系数(只上报)
//Notes:
#define DPID_ELECTRICITY_COE 25
//Fault(只上报)
//Notes:ov_cr：过流保护
#define DPID_FAULT 26
//Led Switch(可下发可上报)
//Notes:
#define DPID_SWITCH_LED 27
//Mode(可下发可上报)
//Notes:
#define DPID_WORK_MODE 28
//Brightness(可下发可上报)
//Notes:
#define DPID_BRIGHT_VALUE 29
//Color Temp(可下发可上报)
//Notes:
#define DPID_TEMP_VALUE 30
//Color Mode(可下发可上报)
//Notes:
#define DPID_COLOUR_DATA 31
//Scene Mode(可下发可上报)
//Notes:
#define DPID_SCENE_DATA 32
//Scene 1(可下发可上报)
//Notes:
#define DPID_FLASH_SCENE_1 33
//Scene 2(可下发可上报)
//Notes:
#define DPID_FLASH_SCENE_2 34
//Scene 3(可下发可上报)
//Notes:
#define DPID_FLASH_SCENE_3 35
//Scene 4(可下发可上报)
//Notes:
#define DPID_FLASH_SCENE_4 36
//Led Countdown(可下发可上报)
//Notes:
#define DPID_COUNTDOWN_LED 37
//全部开关(可下发可上报)
//Notes:
#define DPID_SWITCH_ALL 38


/*****************************************************************************
Function name : all_data_update
Function description : Upload all system dp point information
Input parameter : None
Return parameter : None
Instructions : The MCU must implement the data reporting function within the function
*****************************************************************************/
void all_data_update(void);

#ifdef SUPPORT_MCU_RTC_CHECK
/*****************************************************************************
Function name : mcu_write_rtctime
Function description : The MCU calibrates the local RTC clock
Input parameter : None
Return parameter : None
Instructions : The MCU needs to implement this function on its own
*****************************************************************************/
void mcu_write_rtctime(unsigned char time[]);
#endif

#ifdef WIFI_TEST_ENABLE
/*****************************************************************************
Function name : wifi_test_result
Function description : Wifi function test feedback
Input parameter : result:wifi function test result;0:failure/1:success
           rssi:Test success indicates wifi signal strength / test failure indicates error type
Return parameter : None
Instructions : The MCU needs to implement this function on its own
*****************************************************************************/
void wifi_test_result(unsigned char result,unsigned char rssi);
#endif

#ifdef SUPPORT_MCU_FIRM_UPDATE
/*****************************************************************************
Function name : mcu_firm_update_handle
Function description : The MCU enters the firmware upgrade mode
Input parameter : value:Firmware buffer area
           position:The current packet is in the firmware location
           length:The current firmware package length (when the firmware package length is 0 indicates that the firmware package is sent)
Return parameter : None
Instructions : The MCU needs to implement this function on its own
*****************************************************************************/
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length);
#endif

/*****************************************************************************
Function name : dp_download_handle
Function description : dp issue processing function
Input parameter : dpid:DP serial number
value:dp data buffer address
length:dp data length
Return parameter : Success return:SUCCESS/Failure return:ERRO
Instructions : Users can't change the function
*****************************************************************************/
unsigned char dp_download_handle(unsigned char dpid,const unsigned char value[], unsigned short length);
/*****************************************************************************
Function name : get_download_cmd_total
Function description : Gets the sum of all dp commands
Input parameter : None
Return parameter :  Sum of issueing command
Instructions : The function can not be modified by user
*****************************************************************************/
unsigned char get_download_cmd_total(void);



#endif

