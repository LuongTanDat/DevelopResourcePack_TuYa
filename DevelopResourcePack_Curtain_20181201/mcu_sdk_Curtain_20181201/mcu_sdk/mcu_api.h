/****************************************Copyright (c)*************************
**                             Copyright (C), 2015-2020, Tuya Technology
**
**                                 http://www.tuya.com
**
**--------------File information-------------------------------------------------------
**File name: mcu_api.c
**Description: Issued/reported data processing function
**Instructions : here is no need to change the functions in the file. All files that users need are included in this file. 
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
** Date: 2016－5－26
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
#ifndef __MCU_API_H_
#define __MCU_API_H_


#ifdef MCU_API_GLOBAL
  #define MCU_API_EXTERN
#else
  #define MCU_API_EXTERN   extern
#endif

/*****************************************************************************
Function name : hex_to_bcd
Function description : hex transfers to bcd
Input parameter : Value_H:High byte/Value_L:Low byte
Return parameter : bcd_value:Data after transfer is finished
*****************************************************************************/
unsigned char hex_to_bcd(unsigned char Value_H,unsigned char Value_L);
/*****************************************************************************
Function name : my_strlen
Function description : Get string length
Input parameter :
Return parameter :
*****************************************************************************/
unsigned long my_strlen(unsigned char *str);

/*****************************************************************************
Function name : my_memset
Function description : Set the first count of bytes to character c in the memory area referred by src
Input parameter :
Return parameter :
*****************************************************************************/
void *my_memset(void *src,unsigned char ch,unsigned short count);

/*****************************************************************************
Function name : mymemcpy
Function description : Memory copy
Input parameter :
Return parameter :
*****************************************************************************/
void *my_memcpy(void *dest, const void *src, unsigned short count);
/*****************************************************************************

Function name : int_to_byte
Function name : Split the int by four bytes
Input parameter  : number:4-byte of raw data;value:4 bytes of data after processing is complete
Return parameter :None
****************************************************************************/
void int_to_byte(unsigned long number,unsigned char value[4]);

/*****************************************************************************
Function name : byte_to_int
Function description : Combines 4bit into one 32bit variable
Input parameter : value:4 bytes array
Return parameter : number:32bit variable after combination is complete
****************************************************************************/
unsigned long byte_to_int(const unsigned char value[4]);

#ifndef WIFI_CONTROL_SELF_MODE
/*****************************************************************************
Function name : mcu_get_reset_wifi_flag
Function description : Symbol that MCU successfully obtains Wi-Fi
Input parameter : None
Return parameter  : Reset symbol:RESET_WIFI_ERROR:失败/RESET_WIFI_SUCCESS:成功
Instructions : 1:After MCU calls mcu_reset_wifi(), call the function to get the reset status
           2:If the module is self-processing mode, the MCU does not need to call the function
*****************************************************************************/
unsigned char mcu_get_reset_wifi_flag(void);
/*****************************************************************************
Function name : reset_wifi
Function description : MCU actively resets the Wifi mode of operation
Input parameter : None
Return parameter : None
Instructions : 1:MCU actively calls, get whether wifi reset is successful through mcu_get_reset_wifi_flag() function
           2:If the module is self-processing mode, the MCU does not need to call the function
*****************************************************************************/
void mcu_reset_wifi(void);
/*****************************************************************************
Function name : mcu_get_wifimode_flag
Function description : Symbol to successfully get Wifi status
Input parameter : None
Return parameter : SET_WIFICONFIG_ERROR:Failure/SET_WIFICONFIG_SUCCESS:Success
Instructions : 1:After MCU calls mcu_set_wifi_mode(), call the function to get the reset status
           2:If the module is self-processing mode, the MCU does not need to call the function
*****************************************************************************/
unsigned char mcu_get_wifimode_flag(void);
/*****************************************************************************
Function name : mcu_set_wifi_mode
Function description : MCU set up Wifi mode of operation
Input parameter : mode:
          SMART_CONFIG:Go to smartconfig mode
          AP_CONFIG:Go to AP mode
Return parameter : None
Instructions : 1:MCU actively calls
           2:After success, you can determine whether set_wifi_config_state is TRUE; TRUE indicates that the wifi working mode is successful
           3:If the module is self-processing mode, the MCU does not need to call the function
*****************************************************************************/
void mcu_set_wifi_mode(unsigned char mode);
/*****************************************************************************
Function name: mcu_get_wifi_work_state
Function description  : The MCU actively obtains the current Wifi working state
Input parameter: None
Return parameter : WIFI_WORK_SATE_E:
          SMART_CONFIG_STATE:smartconfig configuration status
          AP_STATE:AP configuration status
          WIFI_NOT_CONNECTED:WIFI configuration is successful but not connected to the router
          WIFI_CONNECTED:WIFI configuration is successful and connected to the router
Instructions : None
*****************************************************************************/
unsigned char mcu_get_wifi_work_state(void);
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/*****************************************************************************
Function name  : mcu_get_system_time
Function description : The MCU acquires system time for calibrating the local clock
Input parameter : None
Return parameter : None
Instructions : After MCU's active call is completed, calibrate rtc clock in mcu_write_rtctime function
*****************************************************************************/
void mcu_get_system_time(void);
#endif

#ifdef WIFI_TEST_ENABLE
/*****************************************************************************
Function name : mcu_start_wifitest
Function description : MCU initiated wifi function test
Input parameter : None
Return parameter : None
Instructions : The MCU needs to call this function on its own
*****************************************************************************/
void mcu_start_wifitest(void);
#endif

/*****************************************************************************
Function name : mcu_dp_raw_update
Function description : raw type dp data upload
Input parameter : dpid:id number
           value:Current dp value pointer
           len:data length
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_raw_update(unsigned char dpid,const unsigned char value[],unsigned short len);

/*****************************************************************************
Function name : mcu_dp_bool_update
Function description : bool type dp data upload
Input parameter : dpid:id number
           value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_bool_update(unsigned char dpid,unsigned char value);

/*****************************************************************************
Function name : mcu_dp_value_update
Function description : value type dp data upload
Input parameter : dpid:id number
           value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value);

/*****************************************************************************
Function name : mcu_dp_string_update
Function description : rstring type dp data upload
Input parameter : dpid:id number
           value:Current dp value pointer
           len:Data length
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_string_update(unsigned char dpid,const unsigned char value[],unsigned short len);

/*****************************************************************************
Function name  : mcu_dp_enum_update
Function description : enum type dp data upload
Input parameter : dpid:id number
           value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_enum_update(unsigned char dpid,unsigned char value);

/*****************************************************************************
Function name : mcu_dp_fault_update
Function description : fault type dp data upload
Input parameter : dpid:id number 
           value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_fault_update(unsigned char dpid,unsigned long value);

/*****************************************************************************
Function name : mcu_get_dp_download_bool
Function description : mcu get booltype issued dp value
Input parameter : value:Dp data buffer address
           length:dp data length
Return parameter : bool:Current dp value
*****************************************************************************/
unsigned char mcu_get_dp_download_bool(const unsigned char value[],unsigned short len);

/*****************************************************************************
Function name : mcu_get_dp_download_value
Function description : Mcu gets the value type issued by the dp value
Input parameter : value:Dp data buffer address
           length:dp data length
Return parameter: value:Current dp value
*****************************************************************************/
unsigned long mcu_get_dp_download_value(const unsigned char value[],unsigned short len);

/*****************************************************************************
Function name : mcu_get_dp_download_enum
Function description : Mcu get the enum type issued dp value
Input parameter : value:Dp data buffer address
           length:dp data length
Return parameter : enum:Current dp value
*****************************************************************************/
unsigned char mcu_get_dp_download_enum(const unsigned char value[],unsigned short len);

/*****************************************************************************
Function name  : uart_receive_input
Function description  : Receive data processing
Input parameter : value:The serial port receives the byte data
Return parameter : None
Instructions : Call the function in the MCU serial port processing function and use the received data as the parameter to be inputted
*****************************************************************************/
void uart_receive_input(unsigned char value);

/*****************************************************************************
Function name  : wifi_uart_service
Function description  : Wifi serial processing services
Input parameter : None
Return parameter : None
Instructions : This function is called in the MCU main function while loop
*****************************************************************************/
void wifi_uart_service(void);

/*****************************************************************************
Function name :  wifi_protocol_init
Function description : Protocol serial port initialization function
Input parameter : None
Return parameter : None
Instructions : The function must be called in the MCU initialization code
*****************************************************************************/
void wifi_protocol_init(void);
/*****************************************************************************
Function name : uart_transmit_output
Function description : Send data processing
Input parameter : value:The serial port receives the byte data
Return parameter : None
Instructions : 请将MCU串口发送函数填入该函数内,并将接收到的数据作为参数传入串口发送函
*****************************************************************************/
void uart_transmit_output(unsigned char value);

#endif