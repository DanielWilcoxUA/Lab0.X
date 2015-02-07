// ******************************************************************************************* //
//
// File:         lab0.c
// Date:         
// Authors:      
//
// Description:  Lab 0 assignment for ECE 372 Spring 2015.
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "initLab0.h"
#include <stdio.h>

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF &
          BKBUG_ON & COE_ON & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum stateTypeEnum{
    L4ON, L4HOLD, L5ON, L5HOLD, L6ON, L6HOLD, L7ON, L7HOLD
} stateType;

#define DELAY 20 //Delay in tenths of a second

volatile stateType state;
volatile int time; //Time that button has been held down in tenths of a second

int main(void)
{
    //Initialize components
    initLEDs();
    initTimer1();
    initSW1();
    state = L4ON; //Start in the first state
    
    while(1)
    {
        //Use a switch statement to define the behavior based on the state
        switch(state){
            case L4ON:
                turnOnLED(4);
                TMR1 = 0;
                time = 0;
                break;
            case L4HOLD:
                turnOnLED(4);
                break;
            case L5ON:
                turnOnLED(5);
                TMR1 = 0;
                time = 0;
                break;
            case L5HOLD:
                turnOnLED(5);
                break;
            case L6ON:
                turnOnLED(6);
                TMR1 = 0;
                time = 0;
                break;
            case L6HOLD:
                turnOnLED(6);
                break;
            case L7ON:
                turnOnLED(7);
                TMR1 = 0;
                time = 0;
                break;
            case L7HOLD:
                turnOnLED(7);
                break;
        }
    }
    return 0;
}

void _ISR _T1Interrupt(void){
    //Put down the timer 1 flag first
    IFS0bits.T1IF = 0;
    time++; //Increment Time
}

void _ISR _CNInterrupt(void) {
    IFS1bits.CNIF = 0;
    switch(state){
        case L4ON:
            //Change state to held state on button press
            if(PORTBbits.RB5==0) state = L4HOLD;
            break;
        case L4HOLD:
            //Change states when button is released, depending
            //on how long the button's been held for
            if(PORTBbits.RB5==1) {
                if(time < DELAY) state = L5ON;
                else state = L7ON;
            }
            break;
        case L5ON:
            if(PORTBbits.RB5==0) state = L5HOLD;
            break;
        case L5HOLD:
            if(PORTBbits.RB5==1) {
                if(time < DELAY) state = L6ON;
                else state = L4ON;
            }
            break;
        case L6ON:
            if(PORTBbits.RB5==0) state = L6HOLD;
            break;
        case L6HOLD:
            if(PORTBbits.RB5==1) {
                if(time < DELAY) state = L7ON;
                else state = L5ON;
            }
            break;
        case L7ON:
            if(PORTBbits.RB5==0) state = L7HOLD;
            break;
        case L7HOLD:
            if(PORTBbits.RB5==1) {
                if(time < DELAY) state = L4ON;
                else state = L6ON;
            }
            break;
    }
}

