
The MCU_SDK is an automatically generated MCU code based on the product functions defined by Tuya Development platform. On this basis, you can modify, add and quickly complete the MCU program. 



Development steps£º

1£ºNeed to do the configuration based on the actual situation of the product(reset wifi button, wifi status indicator process method, whether support MCU upgrade and etc). Please modify the configuration in protocol.h£»
2£ºTransplant this MCU_SDK. Please view the transplant steps in protocol.c file and complete the transplant correctly. After the transplant, please complete the code of data processing and data reporting. Then you can finish all wifi functions. 



File overview£º
This MCU_SDK includes 7 files£º
	£¨1£©protocol.h and protocol.c need to be modified.The protocol.h and protocol.c files have detailed modification description, please read it carefully. 
	£¨2£©The wifi.h file is the general .h file. If you need to call wifi internal features, please #include "wifi.h"¡£
	£¨3£©System.c and system.h are wifi function implementation code, users do not need to modify.
	£¨4£©mcu_api.c and mcu_api.h realize all functions that need to be called by this user. Users do not need to modify.