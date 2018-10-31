/*
|	mcu_api.c 	|	mcu_api.h	|	MCU gọi các hàm liên quan đến xử lý dữ liệu phát sinh hoặc được báo cáo wi-fi trong file này.
|	protocol.c 	|	protocol.h	|	Tùy theo từng trường hợp project, client cần thay đổi 2 file chứa các hàm xử lý dữ liệu
|	system.c 	|	system.h	|
|				|	wifi.h		|
*/


#include "mcu_api.h"

/*
Chuyển string hexa dạng "A2" sang BCD dạng 0x62
*/
unsigned char hex_to_bcd(unsigned char Value_H, unsigned char Value_L);


/*
Trả về độ dài của String truyền vào
*/
unsigned long my_strlen(unsigned char *str);


/*
chuyển số == "count" byte đầu tiên tính từ src thành 'ch'
*/
void *my_memset(void *src, unsigned char ch, unsigned short count);


/*
copy data từ src sang dest
*/
void *my_memcpy(void *dest, const void *src, unsigned short count);


/*
copy data từ src sang dest
*/
void int_to_byte(unsigned long number, unsigned char value[4]);


/*
ngược lại lệnh bên trên
*/
unsigned long byte_to_int(const unsigned char value[4]);


//================================================================================

#ifndef WIFI_CONTROL_SELF_MODE //Nếu wi-fi ở chế độ WIFI_SELF_PROCESSING thì không cần thực hiện các hàm dưới đây

/*
MCU reset chế độ hoạt động của wi-fi
*/
void mcu_reset_wifi(void);


/*
flag kiểm tra quá trình reset wi-fi vừa thực hiện đã thành công không
Return: SMART_CONFIG/AP_CONFIG
*/
unsigned char mcu_get_reset_wifi_flag(void);


/*
Cài đặt mode hoạt động của wi-fi SMART_CONFIG/AP_CONFIG
*/
void mcu_set_wifi_mode(unsigned char mode);


/*
Gọi hàm này sau lệnh mcu_set_wifi_mode
return TRUE nếu chế độ của wi-fi được cài đạt thành công
*/
unsigned char mcu_get_wifimode_flag(void);


/*
Lấy trạng thái làm việc hiện tại của wi-fi:
Return:
- SMART_CONFIG_STATE
- AP_STATE
(cấu hình thành công, nhưng (mất/đã) kết nối)
- WIFI_NOT_CONNECTED
- WIFI_CONNECTED
*/
unsigned char mcu_get_wifi_work_state(void);
#endif


//================================================================================

#ifdef SUPPORT_MCU_RTC_CHECK

/*
khi MCU cần thời gian hệ thống để chỉnh lại đồng hồ thì sử dụng lệnh này
khi lệnh lệnh của MCU được hoàn thành, hàm mcu_write_rtctime được gọi để hiệu chỉnh đồng hộ RTC
*/
void mcu_get_system_time(void);
#endif


//================================================================================

#ifdef WIFI_TEST_ENABLE
/*
MCU khởi tạo chức năng test wifi
*/
void mcu_start_wifitest(void);
#endif


//================================================================================

/*****************************************************************************
Function name : mcu_dp_raw_update
Function description : raw type dp data upload
Input parameter : dpid:id number
		   value:Current dp value pointer
		   len:data length
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_raw_update(unsigned char dpid, const unsigned char value[], unsigned short len);

/*****************************************************************************
Function name : mcu_dp_bool_update
Function description : bool type dp data upload
Input parameter : dpid:id number
		   value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_bool_update(unsigned char dpid, unsigned char value);

/*****************************************************************************
Function name : mcu_dp_value_update
Function description : value type dp data upload
Input parameter : dpid:id number
		   value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_value_update(unsigned char dpid, unsigned long value);

/*****************************************************************************
Function name : mcu_dp_string_update
Function description : rstring type dp data upload
Input parameter : dpid:id number
		   value:Current dp value pointer
		   len:Data length
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_string_update(unsigned char dpid, const unsigned char value[], unsigned short len);

/*****************************************************************************
Function name  : mcu_dp_enum_update
Function description : enum type dp data upload
Input parameter : dpid:id number
		   value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_enum_update(unsigned char dpid, unsigned char value);

/*****************************************************************************
Function name : mcu_dp_fault_update
Function description : fault type dp data upload
Input parameter : dpid:id number
		   value:Current dp value
Return parameter : None
*****************************************************************************/
unsigned char mcu_dp_fault_update(unsigned char dpid, unsigned long value);

/*****************************************************************************
Function name : mcu_get_dp_download_bool
Function description : mcu get booltype issued dp value
Input parameter : value:Dp data buffer address
		   length:dp data length
Return parameter : bool:Current dp value
*****************************************************************************/
unsigned char mcu_get_dp_download_bool(const unsigned char value[], unsigned short len);

/*****************************************************************************
Function name : mcu_get_dp_download_value
Function description : Mcu gets the value type issued by the dp value
Input parameter : value:Dp data buffer address
		   length:dp data length
Return parameter: value:Current dp value
*****************************************************************************/
unsigned long mcu_get_dp_download_value(const unsigned char value[], unsigned short len);

/*****************************************************************************
Function name : mcu_get_dp_download_enum
Function description : Mcu get the enum type issued dp value
Input parameter : value:Dp data buffer address
		   length:dp data length
Return parameter : enum:Current dp value
*****************************************************************************/
unsigned char mcu_get_dp_download_enum(const unsigned char value[], unsigned short len);

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
Instructions : Çë½«MCU´®¿Ú·¢ËÍº¯ÊýÌîÈë¸Ãº¯ÊýÄÚ,²¢½«½ÓÊÕµ½µÄÊý¾Ý×÷Îª²ÎÊý´«Èë´®¿Ú·¢ËÍº¯
*****************************************************************************/
void uart_transmit_output(unsigned char value);

#endif




#include "protocol.h"


/*
Upload tất cả thông tin hệ thống dp
-MCU phải thực hiện hàm báo cáo dữ liệu bên trong hàm
*/
void all_data_update(void);


//================================================================================

#ifdef SUPPORT_MCU_RTC_CHECK
/*
MCU hiệu chỉnh "local RTC clock"
*/
void mcu_write_rtctime(unsigned char time[]);
#endif


//================================================================================

//================================================================================

#ifdef WIFI_TEST_ENABLE
/*
hàm wifi để MCU tự kiểm tra phản hồi 

*/
void wifi_test_result(unsigned char result, unsigned char rssi);
#endif

//================================================================================

//================================================================================
#ifdef SUPPORT_MCU_FIRM_UPDATE
/*
MCU vào chế độ nâng cấp firmware
- value: vùng bộ nhớ đệm của firmware
- position: packet hiện tại đang nằm ở vị trí firmware
- length: độ dài firmware package hiện tại, nếu độ dài bằng 0 --> chỉ rằng firmware package đã được gửi
*/
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length);
#endif
//================================================================================

/*
hàm xử lý vấn đề dp phát sinh
- dpid: số liên tục DP
- value: địa chỉ bộ nhớ đệm dp
- length: độ dài data dp
*/
unsigned char dp_download_handle(unsigned char dpid, const unsigned char value[], unsigned short length);


/*
lấy tổng của tất cả các lệnh dp
*/
unsigned char get_download_cmd_total(void);


#include "system.h"

/*
Viết 1 byte vào wifi_uart buffer
- dest: chỉ số của của mảng buffer muốn được ghi vào
- byte: giá trị của byte
Return: tổng độ dài các byte trong mảng wifi_uart_tx_buf[] đã viết sau khi hoàn thành lệnh
*/
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte);

/*
Viết 1 mảng các byte vào mảng buffer của wifi_uart
- dest: chỉ số của của mảng buffer muốn được ghi byte đầu tiên vào
- src: địa chỉ của mảng muốn truyền vào buffer
- len: độ dài của mảng cần truyền vào
Return: tổng độ dài các byte trong mảng wifi_uart_tx_buf[] đã viết sau khi hoàn thành lệnh
*/
unsigned short set_wifi_uart_buffer(unsigned short dest, unsigned char *src, unsigned short len);

/*
gửi KHUNG DỮ LIỆU tới cho module wi-fi
- fr_type: kiểu khung dữ liệu
- len: độ dài dữ liệu
Return: tổng độ dài các byte trong mảng wifi_uart_tx_buf[] đã viết sau khi hoàn thành lệnh
*/
void wifi_uart_write_frame(unsigned char fr_type, unsigned short len);

/*
tính checksum
- pack: mảng cần tính checksum
- pack_len: độ dài của gói dữ liệu cần tính checksum
Return: Checksum
*/
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len);

/*
Xác định kiểu khung dữ liệu nhận được
- offset: Data start bit
*/
void data_handle(unsigned short offset);

/*
Function name  : get_queue_total_data
Function description: Read the data in the queue
Input parameter  : None
Return parameter : None
*/
unsigned char get_queue_total_data(void);

/*
Function name : Queue_Read_Byte
Function description : Read queue 1 byte data
Input parameter : None
Return parameter  : None
*/
unsigned char Queue_Read_Byte(void);