/*config file*/

//CPU�ͺ����ã�������Ϣ���ã����������ã�����ϵͳ����������ã�

#ifndef __CONFIG_H__
#define __CONFIG_H__

//#define DEBUG 
//#define RELEASE


#define IPMC_DEVSCRIPTION "Booter> "

#define MAX_PIN_GROUP 8

#define AMF_IPMC_DEBUGLED_REVERSE do{GPIOG->ODR ^= 0x400;}while(0)
#define AMF_IPMC_OOSLED_REVERSE do{GPIOG->ODR ^= 0x80;}while(0)

//clock configure
//#define QIUOS_TIME_SLOT  5ms

//#define QIUOS_DEBUG

#define SYS_TERMINAL_UART UART4_IRQHandler()

///////////////////////module layout////////////////////////
/*
# fish
## history
## board
## version
## help
## olupd
## boot




















*/



#endif
/*EOF*/

