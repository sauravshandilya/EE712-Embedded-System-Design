/*---------------------------------------------------------------------------
* Experiment-1 Homework
*
* 	Part-1 Blink Red LED.
*
* 	Description: On pressing switch SW1, toggle Red LED, cycling through delay of 0.5s, 1s and 2s

* Authors:
-- Saurav Shandilya (153076004)
-- Piyush Manavar (153076006)
-- Akshay Kr. Bajpayee ()
*
* Group: Monday-1

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

//---------------------------------------
// Global Variables
//---------------------------------------
volatile int16_t i16ToggleCount = 0;
volatile int16_t binaryCount = 0;
volatile int16_t switchStatus = 0;


/*
* Function Name: hardwareInit()
* Description: Initialize PORTF GPIO pins for LED and Switch. PF1 - Red, PF2 - Blue, PF3 - Green
*/
void hardwareInit(void)
{
	//Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 5 = 40MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	// ADD Tiva-C GPIO setup - enables port, sets pins 1-3 (RGB) pins for output
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	// GPIO PORTF pin 0 and Pin4
	GPIODirModeSet(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0,GPIO_DIR_MODE_IN);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0,GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);
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
 * Function Name: ledToggle()
 * Description: Toggles Red LED
*/
void ledToggle(void)
{
	// LED values - 2=RED, 4=BLUE, 8=GREEN
	if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1))
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
	}
}

/*
 * Function Name: main()
 * Description: Toggle Red LED - cycling through delay of 0.5s, 1s and 2s on every switch press
*/
void main(void)
{

   hardwareInit();							// init hardware via Xware

   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); // all off


   while(1)									// forever loop
   {
	   if (GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4) == 0)
	   {
		   SysCtlDelay(670);			// switch debouncing
		   while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4) == 0);
		   SysCtlDelay(670);
		   switchStatus++;
		   switchStatus = switchStatus%3;
	   }


	   if (switchStatus == 0)
	   {
		   ledToggle();							// toggle LED
		   delay();
	   }

	   if (switchStatus == 1)
	   {
		   ledToggle();							// toggle LED
		   delay();
		   delay();
	   }

	   if (switchStatus == 2)
	   {
		   ledToggle();							// toggle LED
		   delay();
		   delay();
		   delay();
		   delay();
	   }

	   i16ToggleCount += 1;					// keep track of #toggles
   }

}


