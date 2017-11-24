/******************************************************************************
 *
 * www.payitforward.edu.vn
 *
 *****************************************************************************/

/*
 * main.c
 *      Author: minht57
 *      Editor: Thai - PIF.MTU - RYA2017
 */

/******************************************************************************
 * IMPORT
 *****************************************************************************/
#include "include.h"

/******************************************************************************
 * DEFINE
 *****************************************************************************/
//#define TX

/******************************************************************************
 * GLOBAL VARIABLE
 *****************************************************************************/
uint8_t SendData[50];
uint8_t GetData[50];
int tick = GPIO_PIN_3;


void GPIO_Init(void)
{
    //PortF Enable
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //Config GPIO that connect to LED - PIN 1,2,3
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    //Turn off all LEDs
    GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_3, 0);
//    //Config Buttons
//    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
//    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01;
//    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
//    GPIODirModeSet(GPIO_PORTF_BASE,  SW1|SW2, GPIO_DIR_MODE_IN);
//    GPIOPadConfigSet(GPIO_PORTF_BASE, SW1|SW2, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
//    //Config GPIO Interrupt for SW1
//    GPIOIntTypeSet(GPIO_PORTF_BASE,SW1|SW2, GPIO_FALLING_EDGE);
//    GPIOIntRegister(GPIO_PORTF_BASE,&ButtonISR);
//    GPIOIntEnable(GPIO_PORTF_BASE, SW1|SW2);
//    IntEnable(INT_GPIOF);
}

/******************************************************************************
 * MAIN
 *****************************************************************************/
void main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    CC1101_Init();
    GPIO_Init();

    while(1)
    {
#ifdef TX
        UART_C1101_WriteCMD("Hello\n\r");
        SysCtlDelay(SysCtlClockGet()/30);
#else
        if(UART_CC1101_Read_CMD(GetData))
        {
            if(tick == 0)
            {
                tick = GPIO_PIN_3;
            }
            else
            {
                tick = 0;
            }

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, tick);

            UART_C1101_WriteCMD("[1.000000,0.000000]");
        }
        SysCtlDelay(SysCtlClockGet()/30);
#endif

    }
}

/******************************************************************************
 * END OF main.c
 *****************************************************************************/
