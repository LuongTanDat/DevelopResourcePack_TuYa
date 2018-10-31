/****************************************Copyright (c)*************************
**                               Copyright (C), 2015-2020, Tuya Technology
**
**                                 http://www.tuya.com
**
**--------------File information-------------------------------------------------------
**File name: mcu_api.c
**Description: Issued/reported data processing function
**Instructions : There is no need to change the functions in the file. All files that users need are included in this file. 
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
#define MCU_API_GLOBAL

#include "wifi.h"

/*****************************************************************************
Function name : hex_to_bcd
Function description : hex transfers to bcd
Input parameter : Value_H:High byte/Value_L:Low byte
Return parameter : bcd_value:Data after transfer is finished
*****************************************************************************/
unsigned char hex_to_bcd(unsigned char Value_H,unsigned char Value_L)
{
  unsigned char bcd_value;
  
  if((Value_H >= '0') && (Value_H <= '9'))
    Value_H -= '0';
  else if((Value_H >= 'A') && (Value_H <= 'F'))
    Value_H = Value_H - 'A' + 10;
  else if((Value_H >= 'a') && (Value_H <= 'f'))
    Value_H = Value_H - 'a' + 10;
   
  bcd_value = Value_H & 0x0f;
  
  bcd_value <<= 4;
  if((Value_L >= '0') && (Value_L <= '9'))
    Value_L -= '0';
  else if((Value_L >= 'A') && (Value_L <= 'F'))
    Value_L = Value_L - 'a' + 10;
  else if((Value_L >= 'a') && (Value_L <= 'f'))
    Value_L = Value_L - 'a' + 10;
  
  bcd_value |= Value_L & 0x0f;

  return bcd_value;
}
/*****************************************************************************
Function name : my_strlen
Function description : Get string length
Input parameter : src:Source address
Return parameter : len:Data length
*****************************************************************************/
unsigned long my_strlen(unsigned char *str)  
{
  unsigned long len = 0;
  if(str == NULL)
  { 
    return 0;
  }
  
  for(len = 0; *str ++ != '\0'; )
  {
    len ++;
  }
  
  return len;
}
/*****************************************************************************
Function name : my_memset
Function description : Set the first count of bytes to character c in the memory area referred by src 
Input parameter : src:Source address
           ch:Set up characters
           count:Set up data length
Return parameter : src:Source address after data is handled
*****************************************************************************/
void *my_memset(void *src,unsigned char ch,unsigned short count)
{
  unsigned char *tmp = (unsigned char *)src;
  
  if(src == NULL)
  {
    return NULL;
  }
  
  while(count --)
  {
    *tmp ++ = ch;
  }
  
  return src;
}
/*****************************************************************************
Function name : mymemcpy
Function description : Memory copy
Input parameter : dest:Target address
           src:Source address
           count:Number of data copies
Return parameter : src:Source address after data is processed
*****************************************************************************/
void *my_memcpy(void *dest, const void *src, unsigned short count)  
{  
  unsigned char *pdest = (unsigned char *)dest;  
  const unsigned char *psrc  = (const unsigned char *)src;  
  unsigned short i;
  
  if(dest == NULL || src == NULL)
  { 
    return NULL;
  }
  
  if((pdest <= psrc) || (pdest > psrc + count))
  {  
    for(i = 0; i < count; i ++)
    {  
      pdest[i] = psrc[i];  
    }  
  }
  else
  {
    for(i = count; i > 0; i --)
    {  
      pdest[i - 1] = psrc[i - 1];  
    }  
  }  
  
  return dest;  
}
/*****************************************************************************
Function name : int_to_byte
Function description : Split the int by four bytes
Input parameter  : number:4-byte of raw data;value:4 bytes of data after processing is complete
Return parameter :None
****************************************************************************/
void int_to_byte(unsigned long number,unsigned char value[4])
{
  value[0] = number >> 24;
  value[1] = number >> 16;
  value[2] = number >> 8;
  value[3] = number & 0xff;
}
/*****************************************************************************
Function name : byte_to_int
Function description : Combines 4bit into one 32bit variable
Input parameter  : value:4 bytes array
Return parameter : 32bit variable after combination is complete
****************************************************************************/
unsigned long byte_to_int(const unsigned char value[4])
{
  unsigned long nubmer = 0;

  nubmer = (unsigned long)value[0];
  nubmer <<= 8;
  nubmer |= (unsigned long)value[1];
  nubmer <<= 8;
  nubmer |= (unsigned long)value[2];
  nubmer <<= 8;
  nubmer |= (unsigned long)value[3];
  
  return nubmer;
}
#ifndef WIFI_CONTROL_SELF_MODE
/*****************************************************************************
Function name : mcu_get_reset_wifi_flag
Function description : Symbol that MCU successfully obtains Wi-Fi
Input parameter : None
Return parameter : Reset symbol:RESET_WIFI_ERROR:Failed/RESET_WIFI_SUCCESS:Success
Instructions : 1:After MCU calls mcu_reset_wifi(), call the function to get the reset status
           2:If the module is self-processing mode, the MCU does not need to call the function
*****************************************************************************/
unsigned char mcu_get_reset_wifi_flag(void)
{
  return reset_wifi_flag;
}
/*****************************************************************************
Function name : reset_wifi
Function description : MCU actively resets the Wifi mode of operation
Input parameter : None
Return parameter : None
Instructions : 1:MCU actively calls, get whether wifi reset is successful through mcu_get_reset_wifi_flag() function
           2:If the module is self-processing mode, the MCU does not need to call the function
*****************************************************************************/
void mcu_reset_wifi(void)
{
  reset_wifi_flag = RESET_WIFI_ERROR;
  
  wifi_uart_write_frame(WIFI_RESET_CMD, 0);
}
/*****************************************************************************
Function name : mcu_get_wifimode_flag
Function description : Symbol to successfully get Wifi status
Input parameter : None
Return parameter : SET_WIFICONFIG_ERROR:Failure /SET_WIFICONFIG_SUCCESS:Success
Instructions : 1:After MCU calls mcu_set_wifi_mode(), call the function to get the reset status
           2:If the module is self-processing mode, the MCU does not need to call the function
*****************************************************************************/
unsigned char mcu_get_wifimode_flag(void)
{
  return set_wifimode_flag;
}
/*****************************************************************************
Function name : mcu_set_wifi_mode
Function description : MCU set up Wifi mode of operation
Input parameter : mode:
          SMART_CONFIG:Go to smartconfig mode
          AP_CONFIG:Go to AP mode
Return parameter  : None
Instructions : 1:MCU actively calls
           2:After success, you can determine whether set_wifi_config_state is TRUE; TRUE indicates that the wifi working mode is successful
           3:If the module is self-processing mode, the MCU does not need to call the function
*****************************************************************************/
void mcu_set_wifi_mode(unsigned char mode)
{
  unsigned char length = 0;
  
  set_wifimode_flag = SET_WIFICONFIG_ERROR;
  
  length = set_wifi_uart_byte(length, mode);
  
  wifi_uart_write_frame(WIFI_MODE_CMD, length);
}
/*****************************************************************************
Function name : mcu_get_wifi_work_state
Function description : The MCU actively obtains the current Wifi working state
Input parameter : None
Return parameter : WIFI_WORK_SATE_E:
          SMART_CONFIG_STATE:smartconfig configuration status
          AP_STATE:AP configuration status
          WIFI_NOT_CONNECTED:WIFI configuration is successful but not connected to the router
          WIFI_CONNECTED:WIFI configuration is successful and connected to the router
Instructions : None
*****************************************************************************/
unsigned char mcu_get_wifi_work_state(void)
{
  return wifi_work_state;
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/*****************************************************************************
Function name  : mcu_get_system_time
Function description : The MCU acquires system time for calibrating the local clock
Input parameter : None
Return parameter : None
Instructions : After MCU's active call is completed, calibrate rtc clock in mcu_write_rtctime function
*****************************************************************************/
void mcu_get_system_time(void)
{
  wifi_uart_write_frame(GET_LOCAL_TIME_CMD,0);
}e
#endif

#ifdef WIFI_TEST_ENABLE
/*****************************************************************************
Function name  : mcu_start_wifitest
Function description : MCU initiated wifi function test
Input parameter : None
Return parameter : None
Instructions: The MCU needs to call this function on its own
*****************************************************************************/
void mcu_start_wifitest(void)
{
  wifi_uart_write_frame(WIFI_TEST_CMD,0);
}
#endif

/*****************************************************************************
Function name : mcu_dp_raw_update
Function description : raw type dp data upload
Input parameter : dpid:id number
           value:Current dp value pointer
           len:data length
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_raw_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  //
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_RAW);
  //
  length = set_wifi_uart_byte(length,len / 0x100);
  length = set_wifi_uart_byte(length,len % 0x100);
  //
  length = set_wifi_uart_buffer(length,(unsigned char *)value,len);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
Function name : mcu_dp_bool_update
Function description : bool type dp data upload
Input parameter : dpid:id number
           value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_bool_update(unsigned char dpid,unsigned char value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_BOOL);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,1);
  //
  if(value == FALSE)
  {
    length = set_wifi_uart_byte(length,FALSE);
  }
  else
  {
    length = set_wifi_uart_byte(length,1);
  }
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
Function name  : mcu_dp_value_update
Function description : value type dp data upload
Input parameter : dpid:id number
           value:Current dp value
Return parameter  : None
*****************************************************************************/
unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_VALUE);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,4);
  //
  length = set_wifi_uart_byte(length,value >> 24);
  length = set_wifi_uart_byte(length,value >> 16);
  length = set_wifi_uart_byte(length,value >> 8);
  length = set_wifi_uart_byte(length,value & 0xff);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
Function name : mcu_dp_string_update
Function description : rstring type dp data upload
Input parameter : dpid:id number
           value:Current dp value pointer
           len:Data length
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_string_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  //
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_STRING);
  //
  length = set_wifi_uart_byte(length,len / 0x100);
  length = set_wifi_uart_byte(length,len % 0x100);
  //
  length = set_wifi_uart_buffer(length,(unsigned char *)value,len);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
Function name : mcu_dp_enum_update
Function description : enum type dp data upload
Input parameter : dpid:id number
           value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_enum_update(unsigned char dpid,unsigned char value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_ENUM);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,1);
  //
  length = set_wifi_uart_byte(length,value);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
Function name : mcu_dp_fault_update
Function description : fault type dp data upload
Input parameter : dpid:id number 
           value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_fault_update(unsigned char dpid,unsigned long value)
{
  unsigned short length = 0;
   
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_FAULT);
  //
  length = set_wifi_uart_byte(length,0);
  
  if((value | 0xff) == 0xff)
  {
    length = set_wifi_uart_byte(length,1);
    length = set_wifi_uart_byte(length,value);
  }
  else if((value | 0xffff) == 0xffff)
  {
    length = set_wifi_uart_byte(length,2);
    length = set_wifi_uart_byte(length,value >> 8);
    length = set_wifi_uart_byte(length,value & 0xff);
  }
  else
  {
    length = set_wifi_uart_byte(length,4);
    length = set_wifi_uart_byte(length,value >> 24);
    length = set_wifi_uart_byte(length,value >> 16);
    length = set_wifi_uart_byte(length,value >> 8);
    length = set_wifi_uart_byte(length,value & 0xff);
  }    
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);

  return SUCCESS;
}
/*****************************************************************************
Function name : mcu_get_dp_download_bool
Function description : mcu get booltype issued dp value
Input parameter : value:Dp data buffer address
           length:dp data length
Return parameter : bool:Current dp value
*****************************************************************************/
unsigned char mcu_get_dp_download_bool(const unsigned char value[],unsigned short len)
{
  return(value[0]);
}
/*****************************************************************************
Function name : mcu_get_dp_download_enum
Function description : Mcu get the enum type issued dp value
Input parameter : value:Dp data buffer address
           length:dp data length
Return parameter : enum:Current dp value
*****************************************************************************/
unsigned char mcu_get_dp_download_enum(const unsigned char value[],unsigned short len)
{
  return(value[0]);
}
/*****************************************************************************
Function name : mcu_get_dp_download_value
Function description :Mcu gets the value type issued by the dp value
Input parameter : value:Dp data buffer address
           length:dp data length
Return parameter : value:Current dp value
*****************************************************************************/
unsigned long mcu_get_dp_download_value(const unsigned char value[],unsigned short len)
{
  return(byte_to_int(value));
}
/*****************************************************************************
Function name : uart_receive_input
Function description : Receive data processing
Input parameter : value:The serial port receives the byte data
Return parameter : None
Instructions : Call the function in the MCU serial port receiving function and use the received data as the parameter to be inputted
*****************************************************************************/
void uart_receive_input(unsigned char value)
{
  if((queue_in > queue_out) && ((queue_in - queue_out) >= sizeof(wifi_queue_buf)))
  {
    //Data queue is full
  }
  else if((queue_in < queue_out) && ((queue_out  - queue_in) == 0))
  {
    //Data queue is full
  }
  else
  {
    //Data queue is not full
    if(queue_in >= (unsigned char *)(wifi_queue_buf + sizeof(wifi_queue_buf)))
    {
      queue_in = (unsigned char *)(wifi_queue_buf);
    }
    
    *queue_in ++ = value;
  }
}
/*****************************************************************************
Function name  : wifi_uart_service
Function description  : Wifi serial processing services
Input parameter : None
Return parameter : None
Instructions : This function is called in the MCU main function while loop
*****************************************************************************/
void wifi_uart_service(void)
{
  static unsigned short rx_in = 0;
  unsigned short offset = 0;
  unsigned short rx_value_len = 0;             //Optimum frame length
  
  while((rx_in < sizeof(wifi_uart_rx_buf)) && get_queue_total_data() > 0)
  {
    wifi_uart_rx_buf[rx_in ++] = Queue_Read_Byte();
  }
  
  if(rx_in < PROTOCOL_HEAD)
    return;
  
  while((rx_in - offset) >= PROTOCOL_HEAD)
  {
    if(wifi_uart_rx_buf[offset + HEAD_FIRST] != FRAME_FIRST)
    {
      offset ++;
      continue;
    }
    
    if(wifi_uart_rx_buf[offset + HEAD_SECOND] != FRAME_SECOND)
    {
      offset ++;
      continue;
    }  
    
    if(wifi_uart_rx_buf[offset + PROTOCOL_VERSION] != VERSION)
    {
      offset += 2;
      continue;
    }      
    
    rx_value_len = wifi_uart_rx_buf[offset + LENGTH_HIGH] * 0x100 + wifi_uart_rx_buf[offset + LENGTH_LOW] + PROTOCOL_HEAD;
    if(rx_value_len > sizeof(wifi_uart_rx_buf) + PROTOCOL_HEAD)
    {
      offset += 3;
      continue;
    }
    
    if((rx_in - offset) < rx_value_len)
    {
      break;
    }
    
    //Data reception is complete
    if(get_check_sum((unsigned char *)wifi_uart_rx_buf + offset,rx_value_len - 1) != wifi_uart_rx_buf[offset + rx_value_len - 1])
    {
      //Verification error
      offset += 3;
      continue;
    }
    
    data_handle(offset);
    offset += rx_value_len;
  }//end while

  rx_in -= offset;
  if(rx_in > 0)
  {
    my_memcpy(wifi_uart_rx_buf,wifi_uart_rx_buf + offset,rx_in);
  }
}
/*****************************************************************************
Function name :  wifi_protocol_init
Function description : Protocol serial port initialization function
Input parameter : None
Return parameter : None
Instructions : The function must be called in the MCU initialization code
*****************************************************************************/
void wifi_protocol_init(void)
{
  queue_in = (unsigned char *)wifi_queue_buf;
  queue_out = (unsigned char *)wifi_queue_buf;
  //
#ifndef WIFI_CONTROL_SELF_MODE
  wifi_work_state = WIFI_SATE_UNKNOW;
#endif
}


