/*---------------------------------------------------------------------------
* Experiment-1
* 	Part-1 Blink Blue LED
* 	Part-2 Cycle through Red, Blue and Green LEDs

Authors:
* Saurav Shandilya (153076004)
* Piyush Manavar (153076006)
* Akshay Kr. Bajpayee ()

Group: Monday-1

--------------------------------------------------------------------------- */

//------------------------------------------
// TivaWare Header Files
//------------------------------------------
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include <time.h>
#include <math.h>

//---------------------------------------
// Global Variables
//---------------------------------------
volatile int16_t i16ToggleCount = 0;
volatile int16_t binaryCount = 0;
volatile int16_t toggleCount = 0;

/*
* Function Name: hardwareInit()
* Description: Initialize PORTF GPIO pins for toggling the LED. PF1 - Red, PF2 - Blue, PF3 - Green
*/
void hardwareInit(void)
{
	//Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 5 = 40MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	// ADD Tiva-C GPIO setup - enables port, sets pins 1-3 (RGB) pins for output
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
}

/*
 * Function Name: delay()
 * Description: Creates a 500ms delay via TivaWare fxn
*/
void delay(void)
{
	 SysCtlDelay(6700000);		// creates ~500ms delay - TivaWare fxn
}

/*
 * Function Name: Blue blink
 * Description: Toggle Blue LED at internval of 500ms
 */
void blueBlink(void)
{
	for(binaryCount = 0; binaryCount < 2; binaryCount++)
	{
	   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4*binaryCount);
	   delay();								// create a delay of ~1/2sec
	}
}

/*
 * Function Name: rgbCycle
 * Description: Cycle through Red, Blue and Green LEDs at interval of 500ms
 */
void rgbCycle(void)
{
	for (toggleCount = 1; toggleCount <= 3; toggleCount++)
	{
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_INT_PIN_3,pow(2,toggleCount));
		delay();
	}
}

//---------------------------------------------------------------------------
// main()
//---------------------------------------------------------------------------
void main(void)
{

   hardwareInit();							// init hardware via Xware

   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); // all off

   while(1)									// forever loop
   {
	   //blueBlink();			// blink blue LED
	   rgbCycle();				// cycle through RBG LEDs

	   /*
	   	   for(binaryCount = 0; binaryCount < 8; binaryCount++)
	   	   {
	   		   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, binaryCount);
	   		   delay();								// create a delay of ~1/2sec
	   	   }
	   */

	   i16ToggleCount += 1;					// keep track of #toggles
   }

}





