/****************************************Copyright (c)*************************
**                               Copyright (C), 2015-2020, Tuya Technology
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
#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#ifdef SYSTEM_GLOBAL
  #define SYSTEM_EXTERN
#else
  #define SYSTEM_EXTERN   extern
#endif

//=============================================================================
//he byte order of the frame
//=============================================================================
#define         HEAD_FIRST                      0
#define         HEAD_SECOND                     1        
#define         PROTOCOL_VERSION                2
#define         FRAME_TYPE                      3
#define         LENGTH_HIGH                     4
#define         LENGTH_LOW                      5
#define         DATA_START                      6

//=============================================================================
//Data frame type
//=============================================================================
#define         HEAT_BEAT_CMD                   0                               //Heartbeat package
#define         PRODUCT_INFO_CMD                1                               //Product information 
#define         WORK_MODE_CMD                   2                               //Query the module operating mode set by the MCU
#define         WIFI_STATE_CMD                  3                               //wifi working status	
#define         WIFI_RESET_CMD                  4                               //Rest wifi
#define         WIFI_MODE_CMD                   5                               //Select smartconfig/AP mode
#define         DATA_QUERT_CMD                  6                               //Command issued
#define         STATE_UPLOAD_CMD                7                               //Status report	 
#define         STATE_QUERY_CMD                 8                               //Status query  
#define         UPDATE_QUERY_CMD                9                               //Upgrade query
#define         UPDATE_START_CMD                0x0a                            //Upgrade start
#define         UPDATE_TRANS_CMD                0x0b                            //Upgrade transfer
#define         GET_ONLINE_TIME_CMD             0x0c                            //Get system time (GMT)
#define         FACTORY_MODE_CMD                0x0d                            //Go to production test mode   
#define         WIFI_TEST_CMD                   0x0e                            //wifi function test
#define         GET_LOCAL_TIME_CMD              0x1c                            //Get local time                        


//=============================================================================
#define VERSION                 0x00                                            //Protocol version number
#define PROTOCOL_HEAD           0x07                                            //Fixed protocol header length
#define FIRM_UPDATA_SIZE        256                                            //Upgrade package size
#define FRAME_FIRST             0x55
#define FRAME_SECOND            0xaa
//============================================================================= 
SYSTEM_EXTERN unsigned char volatile wifi_queue_buf[PROTOCOL_HEAD + WIFI_UART_QUEUE_LMT];  //Serial port cache
SYSTEM_EXTERN unsigned char wifi_uart_rx_buf[PROTOCOL_HEAD + WIFI_UART_RECV_BUF_LMT];         //Serial receive cache
SYSTEM_EXTERN unsigned char wifi_uart_tx_buf[PROTOCOL_HEAD + WIFIR_UART_SEND_BUF_LMT];        //Serial send cache
//
SYSTEM_EXTERN volatile unsigned char *queue_in;
SYSTEM_EXTERN volatile unsigned char *queue_out;

SYSTEM_EXTERN unsigned char stop_update_flag;

#ifndef WIFI_CONTROL_SELF_MODE
SYSTEM_EXTERN unsigned char reset_wifi_flag;                                                  //Reset wifi symbol(TRUE:Success/FALSE:Failure)
SYSTEM_EXTERN unsigned char set_wifimode_flag;                                                //Set Wifi working mode symbol(TRUE:Success/FALSE:Failure)
SYSTEM_EXTERN unsigned char wifi_work_state;                                                  //wifi module current working status
#endif


/*****************************************************************************
Function name : set_wifi_uart_byte
Function description  : Write wifi_uart byte
Input parameter : dest:The actual address of buffer area;
           byte:Write the byte value
Return parameter : Write the total length after completion
*****************************************************************************/
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte);

/*****************************************************************************
Function name : set_wifi_uart_buffer
Function description : Write wifi_uart_buffer
Input parameter : dest:Target address
           src:Source address
           len:Data length
Return parameter : None
*****************************************************************************/
unsigned short set_wifi_uart_buffer(unsigned short dest, unsigned char *src, unsigned short len);

/*****************************************************************************
Function name : wifi_uart_write_frame
Function description : Send a frame of data to the wifi serial port
Input parameter : fr_type:Frame type
           len:Data length
Return parameter : None
*****************************************************************************/
void wifi_uart_write_frame(unsigned char fr_type, unsigned short len);

/*****************************************************************************
Function name : get_check_sum
Function description : Calculate the checksum
Input parameter : pack:Data source pointer
           pack_len:Calculate the checksum length
Return parameter : Checksum
*****************************************************************************/
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len);

/*****************************************************************************
Function name : data_handle
Function description : Data frame processing
Input parameter : offset:Data start bit
Return parameter : None
*****************************************************************************/
void data_handle(unsigned short offset);

/*****************************************************************************
Function name  : get_queue_total_data
Function description: Read the data in the queue
Input parameter  : None
Return parameter : None
*****************************************************************************/
unsigned char get_queue_total_data(void);

/*****************************************************************************
Function name : Queue_Read_Byte
Function description : Read queue 1 byte data
Input parameter : None
Return parameter  : None
*****************************************************************************/
unsigned char Queue_Read_Byte(void);

#endif
  
  