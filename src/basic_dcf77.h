/*
Library overview:

Focusing on clean code, this Arduino library implements almost the entire public DCF77 standard in C.
It also checks for transmission errors via even parity and queries the 15 bit ("call bit") to rule out problems with the transmitter. 
The blocking pulseIn() function, which is part of the standard Arduino library, is used for this. There are no other dependencies required.
*/

#ifndef basic_dcf77_h
#define basic_dcf77_h

#include <Arduino.h>

#define BIT_0_DURATION 130000 //This value represents the maximum duration in microseconds for which an edge is held in order to interpret a 0. 
#define BIT_1_DURATION 240000 //This value represents the maximum duration for which an edge is held in order to interpret a 1. 
#define min_BIT_0_DURATION 20000 //This value is no longer considered as 0, but as an error pulse.
#define DCF77_STRING_SIZE 59 //This is the bit size of a DCF77 string.
#define TIMEOUT_DURATION 1600000

struct TimeStampDCF77 
{
    //raw DCF77 values are always in two digits
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t weekday;
    uint8_t month;
    uint8_t year;
    uint8_t A1; //Change from CET to CEST or vice-versa.
    uint8_t CEST;
    uint8_t CET;
    int8_t transmitter_fault;	//Only relevant with very good signal
};

//This function makes the port pin assignment. If this function is not called, the default port is 13.
void setupDCF77(uint8_t pin);
//Receives the demodulated DCF signals and writes them into an int array with the size DCF77_STRING_SIZE, which represents the bits of one minute.
int receiveDCF77(uint8_t* bitArray, uint8_t size);
//Extracts and interprets the date and time from the binary DCF string and writes them into a TimeStampDCF77 structure.
//Parity is evaluated via return value: SUCCESS/ERROR_INVALID_VALUE.
int decodeDCF77(uint8_t *bitArray, uint8_t size, TimeStampDCF77 *time);


#endif
