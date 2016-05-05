
#include "commonheader.h"
#include "delay.h"

void timer2_init(void)
{
	uint32_t timer2count = 40000;				// 1ms delay
	//uint32_t ui32Period = 40000000;			// 1s
	//uint32_t ui32Period = 10000000;			// 0.25 s
	/*
	 * PLL = 400MHz. It is divied by 2 before prescaling, 400/2 = 200 MHz. Divide by 5 => 200/5 = 40MHz; Divide by 2.5 => 200/2.5 = 80MHz.
	 * Refer sysctl.h (line 221 onwards) to know various supported division factor.
	 */

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //SYSDIV_5 is 40MHz; SYSDIV_2_5 is 80MHz
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);	// enable Timer 0
	TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);		// timer0 configure mode as periodic - down counting
	TimerLoadSet(TIMER2_BASE, TIMER_A, timer2count -1);		// Load value from which counting will start
	IntEnable(INT_TIMER2A);									// Enable Tiemr0A interrupt
	TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);		// Enable timer interrupt source - Timer A timeout interrupt
	IntMasterEnable();										// Enable Interrupt
	TimerEnable(TIMER2_BASE, TIMER_A);						// Enable Timer
}

void main (void)
{
	TimerBegin();
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	while(1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 14);
		delay_ms(100000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
		delay_ms(100000);

	}




}
