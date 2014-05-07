/*****************************************************************************
* Company:            MUELLER MARTINI ELECTRONIC AG
* Project:
* Target:             PIC16F887
* Type:               main-module
* Description:        main
* Compiler:           ANSI-C
* Filename:           main.c
* Version:            1.0
* Author:             Noah Huetter
* Creation-Date:      07.05.2014
******************************************************************************
* Modification History:
*
* [1.0]    07.05.2014    NHU   first release
*
*****************************************************************************/
#include <stdlib.h>
#include <p33FJ32MC102.h>
#include "basetype.h"
 #include <libpic30.h>



/*****************************************************************************
* STATIC FUNCTION PROTOTYPES
*****************************************************************************/
static void          fInit           (void);

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);

/*****************************************************************************
* DEFINES/CONSTANTS
*****************************************************************************/
#define TIMER_TICK  1000 //in us


#define LED_RED PORTBbits.RB4
#define LED_GRN PORTAbits.RA4


/*****************************************************************************
* MODULE VARIABLES
*****************************************************************************/
tByte bState = 0;

/*****************************************************************************
* MAIN ROUTINE
*****************************************************************************/
/*==========================================================================*/
int main(int argc, char** argv)
/*----------------------------------------------------------------------------
  Description: main
  ==========================================================================*/
{
  fInit();

  for(;;)
  {
    
  }
  return (EXIT_SUCCESS);
}

/*****************************************************************************
* STATIC FUNCTIONS
*****************************************************************************/
/*==========================================================================*/
static void fInit (void)
/*----------------------------------------------------------------------------
  Description: intializes controller
  ==========================================================================*/
{
  RCONbits.SWDTEN = 0;  //disable WDT
  /* digital IOs */
  TRISBbits.TRISB4 = 0; //LED_RED output
  TRISAbits.TRISA4 = 0; //LED_GRN output

  /* Timer 1 for timer tick */
  TMR1 = 0;
  PR1 = TIMER_TICK / 0.1;
  T1CONbits.TCKPS = 0;  //1/1 PS -> 0.1us @ 10MHz FCY
  T1CONbits.TCS = 0;  //internal clk
  IEC0bits.T1IE = 1;    // Enable Timer 1 interrupt
  T1CONbits.TON = 1;  //start timer

}


/*****************************************************************************
* ISR FUNCTIONS
*****************************************************************************/
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void)
{
  IFS0bits.T1IF = 0;
  if(bState == 0)
  {
    LED_RED = 0;
    bState = 1;
  }
  else
  {
    LED_RED = 1;
    bState = 0;
  }
  
}