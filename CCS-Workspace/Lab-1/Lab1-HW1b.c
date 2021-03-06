/*---------------------------------------------------------------------------
* Experiment-1 Homework
*
* 	Part-2 Interface switch SW2
*
* 	Description: Cycle through Red, Green and Blue LEDs every time switch SW2 is pressed.
* 			     Key concept here was to unlock PORTF Pin0 to use SW2.

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

// LOCK_F and CR_F - used for unlocking PORTF pin 0
#define LOCK_F (*((volatile unsigned long *)0x40025520))	// address of GPIOLOCK register
#define CR_F   (*((volatile unsigned long *)0x40025524))	// address of GPIOCR register

//---------------------------------------
// Global Variables
//---------------------------------------
volatile int16_t i16ToggleCount = 0;
volatile int16_t binaryCount = 0;
volatile int16_t switchStatus = 0;
volatile int16_t toggleCount = 0;


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

	// Following two line removes the lock from SW2 interfaced on Pin0
	LOCK_F = 0x4C4F434BU;			// value in GPIOLOCK register to unlock PF0
	CR_F = GPIO_PIN_0|GPIO_PIN_4;	// GPIOCR register - Pin0

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

/*
 * Function Name: main()
 * Description: Cycle through RBG LED every time switch SW2 is pressed.
 * In this experiment we have to unlock PORTF Pin0 on which SW2 was connected.
*/
void main(void)
{

   hardwareInit();

   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); // all off

   rgbCycle();
   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); // all off

   while(1)									// forever loop
   {
	   if (GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0) == 0)
	   {
		   SysCtlDelay(670);			// switch debouncing
		   rgbCycle();
		   while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0) == 0);
		   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); // all off
		   // SysCtlDelay(670);
		   switchStatus++;
	   }
   }
}


