/****************************************Copyright (c)*************************
**                               Copyright (C), 2015-2020, Tuya Technology
**
**                                 http://www.tuya.com
**
**--------------File information-------------------------------------------------------
**File name: protocol.c
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
** Date: 2016-4-15
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

#include "wifi.h"

/******************************************************************************
                                Instructions for Transplantation:
1:The MCU must directly call the wifi_uart_service () function in mcu_api.c in while
2:After the normal initialization of the program is completed, it is recommended not to interrupt the serial port. If you need to interrupt, interrupt time must be short, the interrupt will cause the loss of serial packet. 
3:Do not call the report function within the interrupt / timer interrupt
******************************************************************************/

         
/******************************************************************************
                              Step 1: Initialize
1:Include "wifi.h" in the files that need to use Wifi related files
2:Call the wifi_protocol_init () function in the mcu_api.c file during the MCU initialization
3:Fill the MCU serial port single-byte send function in the uart_transmit_output function in protocol.c file, and delete the #error
4:Call the uart_receive_input function of mcu_api.c file in MCU serial receiving dunction and use the received byte as the parameter to be inputted. 
5:After single-chip goes into the while loop, call wifi_uart_service () function in mcu_api.c file
******************************************************************************/

/******************************************************************************
                        1:dp data point sequence type table
          **This is automatically generated code, if there are changes in the developer platform, please re-download MCU_SDK**         
******************************************************************************/
const DOWNLOAD_CMD_S download_cmd[] =
{
  {DPID_SWITCH_1, DP_TYPE_BOOL},
  {DPID_SWITCH_2, DP_TYPE_BOOL},
  {DPID_SWITCH_3, DP_TYPE_BOOL},
  {DPID_SWITCH_4, DP_TYPE_BOOL},
  {DPID_SWITCH_5, DP_TYPE_BOOL},
  {DPID_SWITCH_6, DP_TYPE_BOOL},
  {DPID_SWITCH_USB1, DP_TYPE_BOOL},
  {DPID_SWITCH_USB2, DP_TYPE_BOOL},
  {DPID_COUNTDOWN_1, DP_TYPE_VALUE},
  {DPID_COUNTDOWN_2, DP_TYPE_VALUE},
  {DPID_COUNTDOWN_3, DP_TYPE_VALUE},
  {DPID_COUNTDOWN_4, DP_TYPE_VALUE},
  {DPID_COUNTDOWN_5, DP_TYPE_VALUE},
  {DPID_COUNTDOWN_6, DP_TYPE_VALUE},
  {DPID_COUNTDOWN_USB1, DP_TYPE_VALUE},
  {DPID_COUNTDOWN_USB2, DP_TYPE_VALUE},
  {DPID_ADD_ELE, DP_TYPE_VALUE},
  {DPID_CUR_CURRENT, DP_TYPE_VALUE},
  {DPID_CUR_POWER, DP_TYPE_VALUE},
  {DPID_CUR_VOLTAGE, DP_TYPE_VALUE},
  {DPID_TEST_BIT, DP_TYPE_VALUE},
  {DPID_VOLTAGE_COE, DP_TYPE_VALUE},
  {DPID_ELECTRIC_COE, DP_TYPE_VALUE},
  {DPID_POWER_COE, DP_TYPE_VALUE},
  {DPID_ELECTRICITY_COE, DP_TYPE_VALUE},
  {DPID_FAULT, DP_TYPE_FAULT},
  {DPID_SWITCH_LED, DP_TYPE_BOOL},
  {DPID_WORK_MODE, DP_TYPE_ENUM},
  {DPID_BRIGHT_VALUE, DP_TYPE_VALUE},
  {DPID_TEMP_VALUE, DP_TYPE_VALUE},
  {DPID_COLOUR_DATA, DP_TYPE_STRING},
  {DPID_SCENE_DATA, DP_TYPE_STRING},
  {DPID_FLASH_SCENE_1, DP_TYPE_STRING},
  {DPID_FLASH_SCENE_2, DP_TYPE_STRING},
  {DPID_FLASH_SCENE_3, DP_TYPE_STRING},
  {DPID_FLASH_SCENE_4, DP_TYPE_STRING},
  {DPID_COUNTDOWN_LED, DP_TYPE_VALUE},
  {DPID_SWITCH_ALL, DP_TYPE_BOOL},
};


/******************************************************************************
                           2:Serial single-byte sending function
Please fill in the function with MCU serial sending function and use the received data as the parameter to be inputtted to serial sending function. 
******************************************************************************/

/*****************************************************************************
Function name : uart_transmit_output
Function description : Send data processing
Input parameter : value:The serial port receives the byte data
Return parameter : None
Instructions : Please fill in the function with MCU serial sending function and use the received data as the parameter to be inputtted to serial sending function.
*****************************************************************************/
void uart_transmit_output(unsigned char value)
{
  #error "Please fill the function with the MCU serial port sending function and delete the line"
/*
  //Example:
  extern void Uart_PutChar(unsigned char value);
  Uart_PutChar(value);	                                //Serial sending function
*/
}
/******************************************************************************
                           Step 2: Implement the specific user function
1:App issued data processing
2:Reported data processing
******************************************************************************/

/******************************************************************************
                            1:The reporting and processing of all data
The current function handles all data reporting(can be issued/can be reported and only reported)
 Need users to implement according to the actual situations:
  1:Need users to implement report reportable/deliverable and reportable only data point??
  2:Need users to implement report reportable only data point??
This function must be called internally for the MCU
Users can also call this function to achieve the reporting of all the data.
******************************************************************************/

//Automatically generate data reporting functions

/*****************************************************************************
Function name : all_data_update
Function description : Upload all system dp point information, to realze the synchronization of App and mcu data. 
Input parameter : None
Return parameter : None
Instructions : This function is called inside the SDK;;
           CU must implement the data reporting function in the function; Including data that is only reported or that can be reported and issued, 
*****************************************************************************/
void all_data_update(void)
{
  #error "please deal reportable/deliverable or reportable only data in here and delete the line"
  /* 
  //The code is automatically generated by platform. Please modify every funtion that can issued and reported or that can only be reported accordinf to actual data. 
  mcu_dp_bool_update(DPID_SWITCH_1,当前Switch 1); //BOOL型数据上报;
  mcu_dp_bool_update(DPID_SWITCH_2,当前Switch 2); //BOOL型数据上报;
  mcu_dp_bool_update(DPID_SWITCH_3,当前Switch 3); //BOOL型数据上报;
  mcu_dp_bool_update(DPID_SWITCH_4,当前Switch 4); //BOOL型数据上报;
  mcu_dp_bool_update(DPID_SWITCH_5,当前Switch 5); //BOOL型数据上报;
  mcu_dp_bool_update(DPID_SWITCH_6,当前Switch 6); //BOOL型数据上报;
  mcu_dp_bool_update(DPID_SWITCH_USB1,当前Switch 7); //BOOL型数据上报;
  mcu_dp_bool_update(DPID_SWITCH_USB2,当前Switch 8); //BOOL型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_1,当前Countdown 1); //VALUE型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_2,当前Countdown 2); //VALUE型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_3,当前Countdown 3); //VALUE型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_4,当前Countdown 4); //VALUE型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_5,当前Countdown 5); //VALUE型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_6,当前Countdown 6); //VALUE型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_USB1,当前Countdown 7); //VALUE型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_USB2,当前Countdown 8); //VALUE型数据上报;
  mcu_dp_value_update(DPID_ADD_ELE,当前Add Electricity); //VALUE型数据上报;
  mcu_dp_value_update(DPID_CUR_CURRENT,当前Current); //VALUE型数据上报;
  mcu_dp_value_update(DPID_CUR_POWER,当前Power); //VALUE型数据上报;
  mcu_dp_value_update(DPID_CUR_VOLTAGE,当前Voltage); //VALUE型数据上报;
  mcu_dp_value_update(DPID_TEST_BIT,当前Test Bit); //VALUE型数据上报;
  mcu_dp_value_update(DPID_VOLTAGE_COE,当前电压校准系数); //VALUE型数据上报;
  mcu_dp_value_update(DPID_ELECTRIC_COE,当前电流校准系数); //VALUE型数据上报;
  mcu_dp_value_update(DPID_POWER_COE,当前功率校准系数); //VALUE型数据上报;
  mcu_dp_value_update(DPID_ELECTRICITY_COE,当前电量校准系数); //VALUE型数据上报;
  mcu_dp_fault_update(DPID_FAULT,当前Fault); //故障型数据上报;
  mcu_dp_bool_update(DPID_SWITCH_LED,当前Led Switch); //BOOL型数据上报;
  mcu_dp_enum_update(DPID_WORK_MODE,当前Mode); //枚举型数据上报;
  mcu_dp_value_update(DPID_BRIGHT_VALUE,当前Brightness); //VALUE型数据上报;
  mcu_dp_value_update(DPID_TEMP_VALUE,当前Color Temp); //VALUE型数据上报;
  mcu_dp_string_update(DPID_COLOUR_DATA,当前Color Mode指针,当前Color Mode数据长度); //STRING型数据上报;
  mcu_dp_string_update(DPID_SCENE_DATA,当前Scene Mode指针,当前Scene Mode数据长度); //STRING型数据上报;
  mcu_dp_string_update(DPID_FLASH_SCENE_1,当前Scene 1指针,当前Scene 1数据长度); //STRING型数据上报;
  mcu_dp_string_update(DPID_FLASH_SCENE_2,当前Scene 2指针,当前Scene 2数据长度); //STRING型数据上报;
  mcu_dp_string_update(DPID_FLASH_SCENE_3,当前Scene 3指针,当前Scene 3数据长度); //STRING型数据上报;
  mcu_dp_string_update(DPID_FLASH_SCENE_4,当前Scene 4指针,当前Scene 4数据长度); //STRING型数据上报;
  mcu_dp_value_update(DPID_COUNTDOWN_LED,当前Led Countdown); //VALUE型数据上报;
  mcu_dp_bool_update(DPID_SWITCH_ALL,当前全部开关); //BOOL型数据上报;

 */
}


/******************************************************************************
                                WARNING!!!    
                            2:Reporting of processing of all data
Automatic code template function, for specifics,users need to achieve their own data processing. 
******************************************************************************/


/*****************************************************************************
Function name : dp_download_switch_1_handle
Function description : on DPID_SWITCH_1 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_1_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_1;
  
  switch_1 = mcu_get_dp_download_bool(value,length);
  if(switch_1 == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_1,switch_1);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_switch_2_handle
Function description : on DPID_SWITCH_2 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_2_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_2;
  
  switch_2 = mcu_get_dp_download_bool(value,length);
  if(switch_2 == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_2,switch_2);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_switch_3_handle
Function description : on DPID_SWITCH_3 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_3_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_3;
  
  switch_3 = mcu_get_dp_download_bool(value,length);
  if(switch_3 == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_3,switch_3);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_switch_4_handle
Function description : on DPID_SWITCH_4 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_4_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_4;
  
  switch_4 = mcu_get_dp_download_bool(value,length);
  if(switch_4 == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_4,switch_4);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_switch_5_handle
Function description : on DPID_SWITCH_5 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_5_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_5;
  
  switch_5 = mcu_get_dp_download_bool(value,length);
  if(switch_5 == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_5,switch_5);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_switch_6_handle
Function description : on DPID_SWITCH_6 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_6_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_6;
  
  switch_6 = mcu_get_dp_download_bool(value,length);
  if(switch_6 == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_6,switch_6);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_switch_usb1_handle
Function description : on DPID_SWITCH_USB1 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_usb1_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_usb1;
  
  switch_usb1 = mcu_get_dp_download_bool(value,length);
  if(switch_usb1 == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_USB1,switch_usb1);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_switch_usb2_handle
Function description : on DPID_SWITCH_USB2 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_usb2_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_usb2;
  
  switch_usb2 = mcu_get_dp_download_bool(value,length);
  if(switch_usb2 == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_USB2,switch_usb2);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_1_handle
Function description : on DPID_COUNTDOWN_1 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_1_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_1;
  
  countdown_1 = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_1,countdown_1);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_2_handle
Function description : on DPID_COUNTDOWN_2 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_2_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_2;
  
  countdown_2 = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_2,countdown_2);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_3_handle
Function description : on DPID_COUNTDOWN_3 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_3_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_3;
  
  countdown_3 = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_3,countdown_3);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_4_handle
Function description : on DPID_COUNTDOWN_4 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_4_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_4;
  
  countdown_4 = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_4,countdown_4);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_5_handle
Function description : on DPID_COUNTDOWN_5 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_5_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_5;
  
  countdown_5 = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_5,countdown_5);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_6_handle
Function description : on DPID_COUNTDOWN_6 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_6_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_6;
  
  countdown_6 = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_6,countdown_6);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_usb1_handle
Function description : on DPID_COUNTDOWN_USB1 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_usb1_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_usb1;
  
  countdown_usb1 = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_USB1,countdown_usb1);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_usb2_handle
Function description : on DPID_COUNTDOWN_USB2 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_usb2_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_usb2;
  
  countdown_usb2 = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_USB2,countdown_usb2);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_add_ele_handle
Function description : on DPID_ADD_ELE processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_add_ele_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long add_ele;
  
  add_ele = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_ADD_ELE,add_ele);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_switch_led_handle
Function description : on DPID_SWITCH_LED processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_led_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_led;
  
  switch_led = mcu_get_dp_download_bool(value,length);
  if(switch_led == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_LED,switch_led);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_work_mode_handle
Function description : on DPID_WORK_MODE processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_work_mode_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isENUM
  unsigned char ret;
  unsigned char work_mode;
  
  work_mode = mcu_get_dp_download_enum(value,length);
  switch(work_mode)
  {
    case 0:
      
      break;
      
    case 1:
      
      break;
      
    case 2:
      
      break;
      
    case 3:
      
      break;
      
    case 4:
      
      break;
      
    case 5:
      
      break;
      
    case 6:
      
      break;
      
    default:
      
      break;
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_enum_update(DPID_WORK_MODE,work_mode);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_bright_value_handle
Function description : on DPID_BRIGHT_VALUE processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_bright_value_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long bright_value;
  
  bright_value = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_BRIGHT_VALUE,bright_value);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_temp_value_handle
Function description : on DPID_TEMP_VALUE processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_temp_value_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long temp_value;
  
  temp_value = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_TEMP_VALUE,temp_value);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_colour_data_handle
Function description : on DPID_COLOUR_DATA processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_colour_data_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isSTRING
  unsigned char ret;
  /*
  //STRING类型数据处理
  unsigned char string_data[8];
  
  string_data[0] = value[0];
  string_data[1] = value[1];
  string_data[2] = value[2];
  string_data[3] = value[3];
  string_data[4] = value[4];
  string_data[5] = value[5];
  string_data[6] = value[6];
  string_data[7] = value[7];
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_string_update(DPID_COLOUR_DATA,value,length);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_scene_data_handle
Function description : on DPID_SCENE_DATA processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_scene_data_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isSTRING
  unsigned char ret;
  /*
  //STRING类型数据处理
  unsigned char string_data[8];
  
  string_data[0] = value[0];
  string_data[1] = value[1];
  string_data[2] = value[2];
  string_data[3] = value[3];
  string_data[4] = value[4];
  string_data[5] = value[5];
  string_data[6] = value[6];
  string_data[7] = value[7];
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_string_update(DPID_SCENE_DATA,value,length);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_flash_scene_1_handle
Function description : on DPID_FLASH_SCENE_1 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_flash_scene_1_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isSTRING
  unsigned char ret;
  /*
  //STRING类型数据处理
  unsigned char string_data[8];
  
  string_data[0] = value[0];
  string_data[1] = value[1];
  string_data[2] = value[2];
  string_data[3] = value[3];
  string_data[4] = value[4];
  string_data[5] = value[5];
  string_data[6] = value[6];
  string_data[7] = value[7];
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_string_update(DPID_FLASH_SCENE_1,value,length);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_flash_scene_2_handle
Function description : on DPID_FLASH_SCENE_2 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_flash_scene_2_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isSTRING
  unsigned char ret;
  /*
  //STRING类型数据处理
  unsigned char string_data[8];
  
  string_data[0] = value[0];
  string_data[1] = value[1];
  string_data[2] = value[2];
  string_data[3] = value[3];
  string_data[4] = value[4];
  string_data[5] = value[5];
  string_data[6] = value[6];
  string_data[7] = value[7];
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_string_update(DPID_FLASH_SCENE_2,value,length);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_flash_scene_3_handle
Function description : on DPID_FLASH_SCENE_3 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_flash_scene_3_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isSTRING
  unsigned char ret;
  /*
  //STRING类型数据处理
  unsigned char string_data[8];
  
  string_data[0] = value[0];
  string_data[1] = value[1];
  string_data[2] = value[2];
  string_data[3] = value[3];
  string_data[4] = value[4];
  string_data[5] = value[5];
  string_data[6] = value[6];
  string_data[7] = value[7];
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_string_update(DPID_FLASH_SCENE_3,value,length);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_flash_scene_4_handle
Function description : on DPID_FLASH_SCENE_4 processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_flash_scene_4_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isSTRING
  unsigned char ret;
  /*
  //STRING类型数据处理
  unsigned char string_data[8];
  
  string_data[0] = value[0];
  string_data[1] = value[1];
  string_data[2] = value[2];
  string_data[3] = value[3];
  string_data[4] = value[4];
  string_data[5] = value[5];
  string_data[6] = value[6];
  string_data[7] = value[7];
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_string_update(DPID_FLASH_SCENE_4,value,length);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_countdown_led_handle
Function description : on DPID_COUNTDOWN_LED processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_countdown_led_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isVALUE
  unsigned char ret;
  unsigned long countdown_led;
  
  countdown_led = mcu_get_dp_download_value(value,length);
  /*
  //VALUE类型数据处理
  
  */
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_value_update(DPID_COUNTDOWN_LED,countdown_led);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}
/*****************************************************************************
Function name : dp_download_switch_all_handle
Function description : on DPID_SWITCH_ALL processing function
Input parameter : value:Source data
        : length:Data length
Return parameter : Successful return:SUCCESS/Failed to return:ERROR
Instructions for use : 可下发可上报type,need to report the result to App after data is dealt with
*****************************************************************************/
static unsigned char dp_download_switch_all_handle(const unsigned char value[], unsigned short length)
{
  //Example: The current DP type isBOOL
  unsigned char ret;
  //0:关/1:开
  unsigned char switch_all;
  
  switch_all = mcu_get_dp_download_bool(value,length);
  if(switch_all == 0)
  {
    //开关关
  }
  else
  {
    //开关开
  }
  
  //处理完DP数据后应有反馈
  ret = mcu_dp_bool_update(DPID_SWITCH_ALL,switch_all);
  if(ret == SUCCESS)
    return SUCCESS;
  else
    return ERROR;
}


/******************************************************************************
                                WARNING!!!                     
This code is called by SDK internally, please realize function data according to the actual dp data. 
******************************************************************************/
#ifdef SUPPORT_MCU_RTC_CHECK
/*****************************************************************************
Function name : mcu_write_rtctime
Function description  : The MCU calibrates the local RTC clock
Input parameter : None
Return parameter : None
Instructions : The MCU needs to implement this function on its own
*****************************************************************************/
void mcu_write_rtctime(unsigned char time[])
{
  #error "Please write your own RTC clock code and delete the line"
  /*
  time [0] is the symbol for whether successfully obtain the time , 0 for failure, 1 for success
  time [1] for year, 0x00 for 2000
  time [2] for the month, starting from 1 to 12 
  time [3] for the date, starting from 1 to 31 
  time [4] for the clock, starting from 0 to 23
  time [5] for minutes, starting from 0 to 59 
  time [6] for seconds, starting from 0 to 59 
  time [7] for the week, from 1 to 7 ends, 1 for Monday
 */
  if(time[0] == 1)
  {
    //Correctly receive the local clock data returned by the wifi module
	 
  }
  else
  {
  	//Get the local clock data error, it is possible that the current wifi module is not networked
  }
}
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
void wifi_test_result(unsigned char result,unsigned char rssi)
{
  #error "Please implement the wifi function test success / failure code yourself, please delete the line after completion"
  if(result == 0)
  {
    //Test failed
    if(rssi == 0x00)
    {
      //Haven't scanned the router named tuya_mdev_test, please check
    }
    else if(rssi == 0x01)
    {
      //The module is not authorized
    }
  }
  else
  {
    //Test success
    //rssi is signal strength(0-100, 0 signal is the worst，100 signal is the strongest)
  }
  
}
#endif

#ifdef SUPPORT_MCU_FIRM_UPDATE
/*****************************************************************************
Function name : mcu_firm_update_handle
Function description : The MCU enters the firmware upgrade mode
Input parameter  : value:Firmware buffer
           position:The current packet is in the firmware location
           length:The current firmware package length (when the firmware package length is 0 indicates that the firmware package is sent)
Return parameter : None
Instructions :The MCU needs to implement this function on its own
*****************************************************************************/
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length)
{
  #error "Please complete the MCU firmware upgrade code, after the completion, please delete the line"
  if(length == 0)
  {
    //The firmware data is sent
    
  }
  else
  {
    //Firmware data processing
  }
  
  return SUCCESS;
}
#endif
/******************************************************************************
                                WARNING!!!                     
Please don't change the following functions!!
******************************************************************************/

/*****************************************************************************
Function name : dp_download_handle
Function description : Dp issue processing function
Input parameter : dpid:DP serial number
           value:Dp data buffer address
           length:dp data length
Return parameter : Success return:SUCCESS/Failure return:ERRO
Instructions : Users can't change the function
*****************************************************************************/
unsigned char dp_download_handle(unsigned char dpid,const unsigned char value[], unsigned short length)
{
  /*********************************
  Current function process the calling of data that can be issued and reported                    
  Specific function needs to implement the processing of issued data
  Need to feedback the result to App terminal, otherwise App will diagnose the issuing is failed
  ***********************************/
  unsigned char ret;
  switch(dpid)
  {
    case DPID_SWITCH_1:
      //Switch 1processing function
      ret = dp_download_switch_1_handle(value,length);
      break;
    case DPID_SWITCH_2:
      //Switch 2processing function
      ret = dp_download_switch_2_handle(value,length);
      break;
    case DPID_SWITCH_3:
      //Switch 3processing function
      ret = dp_download_switch_3_handle(value,length);
      break;
    case DPID_SWITCH_4:
      //Switch 4processing function
      ret = dp_download_switch_4_handle(value,length);
      break;
    case DPID_SWITCH_5:
      //Switch 5processing function
      ret = dp_download_switch_5_handle(value,length);
      break;
    case DPID_SWITCH_6:
      //Switch 6processing function
      ret = dp_download_switch_6_handle(value,length);
      break;
    case DPID_SWITCH_USB1:
      //Switch 7processing function
      ret = dp_download_switch_usb1_handle(value,length);
      break;
    case DPID_SWITCH_USB2:
      //Switch 8processing function
      ret = dp_download_switch_usb2_handle(value,length);
      break;
    case DPID_COUNTDOWN_1:
      //Countdown 1processing function
      ret = dp_download_countdown_1_handle(value,length);
      break;
    case DPID_COUNTDOWN_2:
      //Countdown 2processing function
      ret = dp_download_countdown_2_handle(value,length);
      break;
    case DPID_COUNTDOWN_3:
      //Countdown 3processing function
      ret = dp_download_countdown_3_handle(value,length);
      break;
    case DPID_COUNTDOWN_4:
      //Countdown 4processing function
      ret = dp_download_countdown_4_handle(value,length);
      break;
    case DPID_COUNTDOWN_5:
      //Countdown 5processing function
      ret = dp_download_countdown_5_handle(value,length);
      break;
    case DPID_COUNTDOWN_6:
      //Countdown 6processing function
      ret = dp_download_countdown_6_handle(value,length);
      break;
    case DPID_COUNTDOWN_USB1:
      //Countdown 7processing function
      ret = dp_download_countdown_usb1_handle(value,length);
      break;
    case DPID_COUNTDOWN_USB2:
      //Countdown 8processing function
      ret = dp_download_countdown_usb2_handle(value,length);
      break;
    case DPID_ADD_ELE:
      //Add Electricityprocessing function
      ret = dp_download_add_ele_handle(value,length);
      break;
    case DPID_SWITCH_LED:
      //Led Switchprocessing function
      ret = dp_download_switch_led_handle(value,length);
      break;
    case DPID_WORK_MODE:
      //Modeprocessing function
      ret = dp_download_work_mode_handle(value,length);
      break;
    case DPID_BRIGHT_VALUE:
      //Brightnessprocessing function
      ret = dp_download_bright_value_handle(value,length);
      break;
    case DPID_TEMP_VALUE:
      //Color Tempprocessing function
      ret = dp_download_temp_value_handle(value,length);
      break;
    case DPID_COLOUR_DATA:
      //Color Modeprocessing function
      ret = dp_download_colour_data_handle(value,length);
      break;
    case DPID_SCENE_DATA:
      //Scene Modeprocessing function
      ret = dp_download_scene_data_handle(value,length);
      break;
    case DPID_FLASH_SCENE_1:
      //Scene 1processing function
      ret = dp_download_flash_scene_1_handle(value,length);
      break;
    case DPID_FLASH_SCENE_2:
      //Scene 2processing function
      ret = dp_download_flash_scene_2_handle(value,length);
      break;
    case DPID_FLASH_SCENE_3:
      //Scene 3processing function
      ret = dp_download_flash_scene_3_handle(value,length);
      break;
    case DPID_FLASH_SCENE_4:
      //Scene 4processing function
      ret = dp_download_flash_scene_4_handle(value,length);
      break;
    case DPID_COUNTDOWN_LED:
      //Led Countdownprocessing function
      ret = dp_download_countdown_led_handle(value,length);
      break;
    case DPID_SWITCH_ALL:
      //全部开关processing function
      ret = dp_download_switch_all_handle(value,length);
      break;

  default:
    break;
  }
  return ret;
}
/*****************************************************************************
Function name : get_download_cmd_total
Function description : Gets the sum of all dp commands
Input parameter : None
Return parameter : Sum of issueing command
Instructions : The function can not be modified by user
*****************************************************************************/
unsigned char get_download_cmd_total(void)
{
  return(sizeof(download_cmd) / sizeof(download_cmd[0]));
}
