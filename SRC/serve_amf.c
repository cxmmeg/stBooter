
#include "config.h"
#include "system.h"
#include "version.h"
#include "Ymodem.h"
#include "flash_if.h"

unsigned long long bootTick = 0;

void srvAmfEarlyInit()
{
    usartBufferInit();

}


void srvAmfDC12vIpmcUpCtrOn(void)
{
    int i;
    //GPIOG->BSRRH = 1UL <<  11;//12v DC
    GPIOE->ODR |= 1UL <<  3;
    i=0xffffff;
    while(--i);
        ;
}

void srvAmfPayloadOn(void)
{
    //GPIOB->BSRRH = 1UL <<  13;//payload
    GPIOB->BSRRL |= 1UL <<  13;

}

void srvAmfPayloadOff(void)
{
    GPIOB->BSRRH |= 1UL <<  13;//payload
}


void srvAmfDC12vOn(void)
{
    int i;
    //GPIOG->BSRRH = 1UL <<  11;//12v DC
    GPIOG->ODR |= 1UL <<  11;
    //delay a little bit
    i=1000;
    while(i--)
        ;

}

int srvBoardInit()
{
    srvAmfEarlyInit();
    bootloader_stage1();
    fish_init();
    
#ifndef BARE_ENVIRONMENT
    srvAmfPayloadOff();
    while(!AMF_SYS_48V_ALARM)
    {
    //����48vģ���i2c�ӿڣ���������Ϣ��¼��sys_data�ṹ����
    // sys_data.pim48vdc_alarm = module_48vdc_alarm();
    }
    
    srvAmfDC12vIpmcUpCtrOn();
    srvAmfDC12vOn();
	
   	while(!AMF_SYS_POWEROK)
        ;
#endif
}

int srvSleep(unsigned int sec)
{
    unsigned long long curTick;
    curTick = bootTick;
    while((bootTick - curTick) < (10 * sec))
    ;
    return 0;
}

int srvLoadApp()
{
	pFunction Jump_To_Application;
    uint32_t JumpAddress;

    JumpAddress = *(__IO uint32_t *)(APPLICATION_ADDRESS + 4);
    Jump_To_Application = (pFunction) JumpAddress;
    __set_MSP(*(uint32_t *)APPLICATION_ADDRESS);
    //before entering a new application, you should disable all NVIC
    
    NVIC->ICER[0] = 0xffffffff;
    NVIC->ICER[1] = 0xffffffff;
    NVIC->ICER[2] = 0xffffffff;
    NVIC->ICER[3] = 0xffffffff;
    NVIC->ICER[4] = 0xffffffff;
    NVIC->ICER[5] = 0xffffffff;
    NVIC->ICER[6] = 0xffffffff;
    NVIC->ICER[7] = 0xffffffff;
    NVIC_SetVectorTable(0x8000000, 0x4000);
    __disable_irq();
    Jump_To_Application();

}
////////////////system tick handler////////////
void SysTick_Handler(void)
{
    bootTick ++;
}

