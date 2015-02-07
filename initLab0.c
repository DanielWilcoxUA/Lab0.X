/*
* File:   initLab0.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include "p24fj64ga002.h"
#include "initLab0.h"

void initLEDs(){
    //Initialize the pin connected to the LEDs as outputs
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;

    //Turn each LED OFF
    LED4 = OFF;
    LED5 = OFF;
    LED6 = OFF;
    LED7 = OFF;
}

void initSW1(){
    //Initialize the pin connected to the switch as an input.
    TRISBbits.TRISB5 = 1;
    IFS1bits.CNIF = 0; //Lower interrupt flag
    IEC1bits.CNIE = 1; //Enable change notification interrupt
    CNEN2bits.CN27IE = 1; //Enable CN interrupt for SW1
}


void initTimer1(){
    //Initialize the timer
    T1CONbits.TCKPS = 0b11; //Set prescalar value to 256
    T1CONbits.TON = 1; //Turn on timer
    IEC0bits.T1IE = 1; //Enable timer interrupt
    IFS0bits.T1IF = 0; //Lower interrupt flag
    PR1 = 0.1 * FREQ / 256.0 - 1; //Set delay to one tenth of a second
}

void turnOnLED(int LED) {
    switch(LED) {
        case 4:
            LED4 = ON;
            LED5 = OFF;
            LED6 = OFF;
            LED7 = OFF;
            break;
        case 5:
            LED4 = OFF;
            LED5 = ON;
            LED6 = OFF;
            LED7 = OFF;
            break;
        case 6:
            LED4 = OFF;
            LED5 = OFF;
            LED6 = ON;
            LED7 = OFF;
            break;
        case 7:
            LED4 = OFF;
            LED5 = OFF;
            LED6 = OFF;
            LED7 = ON;
            break;
        default:
            //Do nothing
            break;
    }
}