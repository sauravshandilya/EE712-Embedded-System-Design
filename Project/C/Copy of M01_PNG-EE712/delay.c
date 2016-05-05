/*
 * delay.c
 *
 *  Created on: 04-Feb-2016
 *  Author: saurav
 *  Description: Generates delay of 1ms when function delay_ms(1) is called.
 */

#include "commonheader.h"		// contains all required header files
#include "delay.h"				//

volatile unsigned millis = 0;
unsigned delayval;

void Timer0IntHandler(void)
{
	  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	  millis++;
}

void TimerBegin_ms(void)
{
	uint32_t ui32Period = 40000;				// 1ms delay
	//uint32_t ui32Period = 40000000;			// 1s
	//uint32_t ui32Period = 10000000;			// 0.25 s
	//uint32_t ui32Period = 40;				// 1us delay
	/*
	 * PLL = 400MHz. It is divied by 2 before prescaling, 400/2 = 200 MHz. Divide by 5 => 200/5 = 40MHz; Divide by 2.5 => 200/2.5 = 80MHz.
	 * Refer sysctl.h (line 221 onwards) to know various supported division factor.
	 */

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //SYSDIV_5 is 40MHz; SYSDIV_2_5 is 80MHz
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);	// enable Timer 0
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);		// timer0 configure mode as periodic - down counting
	TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);		// Load value from which counting will start
	IntEnable(INT_TIMER0A);									// Enable Tiemr0A interrupt
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);		// Enable timer interrupt source - Timer A timeout interrupt
	IntMasterEnable();										// Enable Interrupt
	TimerEnable(TIMER0_BASE, TIMER_A);						// Enable Timer

}

void TimerBegin_us(void)
{
	uint32_t ui32Period = 40;				// 1us delay
	/*
	 * PLL = 400MHz. It is divied by 2 before prescaling, 400/2 = 200 MHz. Divide by 5 => 200/5 = 40MHz; Divide by 2.5 => 200/2.5 = 80MHz.
	 * Refer sysctl.h (line 221 onwards) to know various supported division factor.
	 */

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //SYSDIV_5 is 40MHz; SYSDIV_2_5 is 80MHz
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);	// enable Timer 0
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);		// timer0 configure mode as periodic - down counting
	TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);		// Load value from which counting will start
	IntEnable(INT_TIMER0A);									// Enable Tiemr0A interrupt
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);		// Enable timer interrupt source - Timer A timeout interrupt
	IntMasterEnable();										// Enable Interrupt
	TimerEnable(TIMER0_BASE, TIMER_A);						// Enable Timer

}
void delay_ms (unsigned delayval)
{
	volatile unsigned temp = millis;
	TimerBegin_ms();

	while ( (millis-temp) < delayval);
	//while (millis < 1);
	//millis = 0;
}

void delay_us (unsigned delayval)
{
	volatile unsigned temp = millis;
	TimerBegin_us();

	while ( (millis-temp) < delayval);
}
