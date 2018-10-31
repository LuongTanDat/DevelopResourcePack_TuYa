/****************************************Copyright (c)*************************
**                              Copyright (C), 2015-2020, Tuya Technology
**
**                                 http://www.tuya.com
**
**--------------File information-------------------------------------------------------
**File name: system.c
**Description: Wifi data processing function
**Instructions : The user does not need to care about the file implementation
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
#define SYSTEM_GLOBAL

#include "wifi.h"
//
//
extern const DOWNLOAD_CMD_S download_cmd[];

/*****************************************************************************
Function name        : set_wifi_uart_byte
Function description : write wifi_uart bytes
Input parameter      : dest: real address of the buffer;
                       byte: value of the byte to write
Return parameter     : total length after the completion of write
*****************************************************************************/
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte)
{
  unsigned char *obj = (unsigned char *)wifi_uart_tx_buf + DATA_START + dest;
  
  *obj = byte;
  dest += 1;
  
  return dest;
}
/*****************************************************************************
Function name : set_wifi_uart_buffer
Function description : Write wifi_uart_buffer
Input parameter : dest:Target address
           src:Source address
           len:Data length
Return parameter : None
*****************************************************************************/
unsigned short set_wifi_uart_buffer(unsigned short dest, unsigned char *src, unsigned short len)
{
  unsigned char *obj = (unsigned char *)wifi_uart_tx_buf + DATA_START + dest;
  
  my_memcpy(obj,src,len);
  
  dest += len;
  return dest;
}
/*****************************************************************************
Function name : wifi_uart_write_data
Function description : Write continuous data to wifi uart
Input parameter : in:Send the cache pointer
           len:Data transmission length
Return parameter : None
*****************************************************************************/
static void wifi_uart_write_data(unsigned char *in, unsigned short len)
{
  if((NULL == in) || (0 == len))
  {
    return;
  }
  
  while(len --)
  {
    uart_transmit_output(*in);
    in ++;
  }
}
/*****************************************************************************
Function name : get_check_sum
Function description : Calculate the checksum
Input parameter : pack:Data source pointer
           pack_len:Calculate the checksum length
Return parameter : Checksum
*****************************************************************************/
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len)
{
  unsigned short i;
  unsigned char check_sum = 0;
  
  for(i = 0; i < pack_len; i ++)
  {
    check_sum += *pack ++;
  }
  
  return check_sum;
}
/*****************************************************************************
Function name : wifi_uart_write_frame
Function description : Send a frame of data to the wifi serial port
Input parameter : fr_type:Frame type
           len:Data length
Return parameter : None
*****************************************************************************/
void wifi_uart_write_frame(unsigned char fr_type, unsigned short len)
{
  unsigned char check_sum = 0;
  
  wifi_uart_tx_buf[HEAD_FIRST] = 0x55;
  wifi_uart_tx_buf[HEAD_SECOND] = 0xaa;
  wifi_uart_tx_buf[PROTOCOL_VERSION] = 0x01;
  wifi_uart_tx_buf[FRAME_TYPE] = fr_type;
  wifi_uart_tx_buf[LENGTH_HIGH] = len >> 8;
  wifi_uart_tx_buf[LENGTH_LOW] = len & 0xff;
  
  len += PROTOCOL_HEAD;
  check_sum = get_check_sum((unsigned char *)wifi_uart_tx_buf, len - 1);
  wifi_uart_tx_buf[len - 1] = check_sum;
  //
  wifi_uart_write_data((unsigned char *)wifi_uart_tx_buf, len);
}
/*****************************************************************************
Function name : heat_beat_check
Function description : Heatbeat detection
Input parameter : None
Return parameter : None
*****************************************************************************/
static void heat_beat_check(void)
{
  unsigned char length = 0;
  static unsigned char mcu_reset_state = FALSE;
  
  if(FALSE == mcu_reset_state)
  {
    length = set_wifi_uart_byte(length,FALSE);
    mcu_reset_state = TRUE;
  }
  else
  {
    length = set_wifi_uart_byte(length,TRUE);
  }
  
  wifi_uart_write_frame(HEAT_BEAT_CMD, length);
}
/*****************************************************************************
Function name  : product_info_update
Function description   : Product information upload
Input parameter : None
Return parameter : None
*****************************************************************************/
static void product_info_update(void)
{
  unsigned char length = 0;
  
  length = set_wifi_uart_buffer(length,(unsigned char *)PRODUCT_KEY,my_strlen((unsigned char *)PRODUCT_KEY));
  length = set_wifi_uart_buffer(length,(unsigned char *)MCU_VER,my_strlen((unsigned char *)MCU_VER));
  
  wifi_uart_write_frame(PRODUCT_INFO_CMD, length);
}
/*****************************************************************************
Function name : get_mcu_wifi_mode
Function description : Query mcu and wifi work mode
Input parameter  : None
Return parameter : None
*****************************************************************************/
static void get_mcu_wifi_mode(void)
{
  unsigned char length = 0;
  
#ifdef WIFI_CONTROL_SELF_MODE                                   //Module self processing
  length = set_wifi_uart_byte(length, WF_STATE_KEY);
  length = set_wifi_uart_byte(length, WF_RESERT_KEY);
#else                                                           
  //No need to process data
#endif
  
  wifi_uart_write_frame(WORK_MODE_CMD, length);
}
/*****************************************************************************
Function name : get_update_dpid_index
Function description : Perhaps make the serial number of the DPID in the array
Input parameter : dpid:dpid
Return parameter : index:Dp serial number
*****************************************************************************/
static unsigned char get_dowmload_dpid_index(unsigned char dpid)
{
  unsigned char index;
  unsigned char total = get_download_cmd_total();
  
  for(index = 0; index < total; index ++)
  {
    if(download_cmd[index].dp_id == dpid)
    {
      break;
    }
  }
  
  return index;
}
/*****************************************************************************
Function name  : data_point_handle
Function description : Issued data processing
Input parameter : value:Issued data source pointer
Return parameter : ret:Returning data processing result
*****************************************************************************/
static unsigned char data_point_handle(const unsigned char value[])
{
  unsigned char dp_id,index;
  unsigned char dp_type;
  unsigned char ret;
  unsigned short dp_len;
  
  dp_id = value[0];
  dp_type = value[1];
  dp_len = value[2] * 0x100;
  dp_len += value[3];
  
  index = get_dowmload_dpid_index(dp_id);

  if(dp_type != download_cmd[index].dp_type)
  {
    //Error message
    return FALSE;
  }
  else
  {
    ret = dp_download_handle(dp_id,value + 4,dp_len);
  }
  
  return ret;
}
/*****************************************************************************
Function name : data_handle
Function description : Data frame processing
Input parameter : offset:Data start bit
Return parameter : None
*****************************************************************************/
void data_handle(unsigned short offset)
{
#ifdef SUPPORT_MCU_FIRM_UPDATE
  unsigned char *firmware_addr;
  static unsigned long firm_length;                                             //MCU upgrade file length
  static unsigned char firm_update_flag;                                        //MCU upgrade symbol
  unsigned long dp_len;
#else
  unsigned short dp_len;
#endif
  
  unsigned char ret;
  unsigned short i,total_len;
  unsigned char cmd_type = wifi_uart_rx_buf[offset + FRAME_TYPE];
  
  switch(cmd_type)
  {
  case HEAT_BEAT_CMD:                                   //Heartbeat bag
    heat_beat_check();
    break;
    
  case PRODUCT_INFO_CMD:                                //Product information
    product_info_update();
    break;
    
  case WORK_MODE_CMD:                                   //Query the module operating mode set by the MCU
    get_mcu_wifi_mode();
    break;
    
#ifndef WIFI_CONTROL_SELF_MODE
  case WIFI_STATE_CMD:                                  //Wifi working state
    wifi_work_state = wifi_uart_rx_buf[offset + DATA_START];
    wifi_uart_write_frame(WIFI_STATE_CMD,0);
    break;

  case WIFI_RESET_CMD:                                  //Reset wifi (wifi return success)
    reset_wifi_flag = RESET_WIFI_SUCCESS;
    break;
    
  case WIFI_MODE_CMD:                                   //Select smartconfig/AP mode(wifi return success)	
    set_wifimode_flag = SET_WIFICONFIG_SUCCESS;
    break;
#endif
    
  case DATA_QUERT_CMD:                                  //Command issued
    total_len = wifi_uart_rx_buf[offset + LENGTH_HIGH] * 0x100;
    total_len += wifi_uart_rx_buf[offset + LENGTH_LOW];
    
    for(i = 0;i < total_len;)
    {
      dp_len = wifi_uart_rx_buf[offset + DATA_START + i + 2] * 0x100;
      dp_len += wifi_uart_rx_buf[offset + DATA_START + i + 3];
      //
      ret = data_point_handle((unsigned char *)wifi_uart_rx_buf + offset + DATA_START + i);
      
      if(SUCCESS == ret)
      {
        //Success message
      }
      else
      {
        //Error message
      }
      
      i += (dp_len + 4);
    }
    
    break;
    
  case STATE_QUERY_CMD:                                 //Status query
    all_data_update();                               
    break;
    
#ifdef SUPPORT_MCU_FIRM_UPDATE
  case UPDATE_START_CMD:                                //The upgrade starts
    firm_length = wifi_uart_rx_buf[offset + DATA_START];
    firm_length <<= 8;
    firm_length |= wifi_uart_rx_buf[offset + DATA_START + 1];
    firm_length <<= 8;
    firm_length |= wifi_uart_rx_buf[offset + DATA_START + 2];
    firm_length <<= 8;
    firm_length |= wifi_uart_rx_buf[offset + DATA_START + 3];
    //
    wifi_uart_write_frame(UPDATE_START_CMD,0);
    firm_update_flag = UPDATE_START_CMD;
     break;
    
  case UPDATE_TRANS_CMD:                                //Upgrade transmission
    if(firm_update_flag == UPDATE_START_CMD)
    {
      //Stop all data reporting
      stop_update_flag = ENABLE;                                                 
      
      total_len = wifi_uart_rx_buf[offset + LENGTH_HIGH] * 0x100;
      total_len += wifi_uart_rx_buf[offset + LENGTH_LOW];
      
      dp_len = wifi_uart_rx_buf[offset + DATA_START];
      dp_len <<= 8;
      dp_len |= wifi_uart_rx_buf[offset + DATA_START + 1];
      dp_len <<= 8;
      dp_len |= wifi_uart_rx_buf[offset + DATA_START + 2];
      dp_len <<= 8;
      dp_len |= wifi_uart_rx_buf[offset + DATA_START + 3];
      
      firmware_addr = wifi_uart_rx_buf + offset + DATA_START + 4;
      if((total_len == 4) && (dp_len == firm_length))
      {
        //he last pack
        ret = mcu_firm_update_handle(firmware_addr,dp_len,0);
        
        firm_update_flag = 0;
      }
      else if((total_len - 4) <= FIRM_UPDATA_SIZE)
      {
        ret = mcu_firm_update_handle(firmware_addr,dp_len,total_len - 4);
      }
      else
      {
        firm_update_flag = 0;
        ret = ERROR;
      }
      
      if(ret == SUCCESS)
      {
        wifi_uart_write_frame(UPDATE_TRANS_CMD,0);
      }
      //Restore all data reporting
      stop_update_flag = DISABLE;    
    }
    break;
#endif      
    
#ifdef SUPPORT_MCU_RTC_CHECK
  case GET_LOCAL_TIME_CMD:                             //get local time
      mcu_write_rtctime(wifi_uart_rx_buf + offset + DATA_START);
    break;
#endif
 
#ifdef WIFI_TEST_ENABLE
  case WIFI_TEST_CMD:                                   //wifi function test
    wifi_test_result(wifi_uart_rx_buf[offset + DATA_START],wifi_uart_rx_buf[offset + DATA_START + 1]);
    break;
#endif
    
  default:
    break;
  }
}
/*****************************************************************************
Function name : get_queue_total_data
Function description : Read the data in the queue
Input parameter : None
Return parameter : None
*****************************************************************************/
unsigned char get_queue_total_data(void)
{
  if(queue_in != queue_out)
    return 1;
  else
    return 0;
}
/*****************************************************************************
Function name : Queue_Read_Byte
Function description : Read queue 1 byte data
Input parameter : None
Return parameter : None
*****************************************************************************/
unsigned char Queue_Read_Byte(void)
{
  unsigned char value;
  
  if(queue_out != queue_in)
  {
    //Have data
    if(queue_out >= (unsigned char *)(wifi_queue_buf + sizeof(wifi_queue_buf)))
    {
      //The data is already at the end
      queue_out = (unsigned char *)(wifi_queue_buf);
    }
    
    value = *queue_out ++;   
  }
  
  return value;
}

