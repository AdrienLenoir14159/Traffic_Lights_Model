#ifndef INITIALISATIONS
#define INITIALISATIONS
//----------


#include "stm32f4xx.h"

#define AHB1_RCC 0x40023830
#define monGPIOA 0x40020000
#define monGPIOB 0x40020400
#define monGPIOC 0x40020800

void PortClockInit(int);
void PinInInit(int,int);
void PinOutInit(int,int);
int pinInRead(int,int);
void pinOutWrite(int,int,int);

//----------
#endif