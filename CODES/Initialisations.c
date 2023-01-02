#include "Initialisations.h"

void PortClockInit(int adresseGPIO){
	int pin = (adresseGPIO - 0x40020000)/0x400;
	int *emplacement = (int*) AHB1_RCC;
	int masqueOU = 1 << pin;
	*emplacement |= masqueOU;
}

void PinInInit(int adresseGPIO, int pin){

	// ********** POUR INPUT PULL DOWN **********

	int *emplacement = (int*) adresseGPIO;
	int masqueET = 0;
	int masqueOU = 0;
	// On modifie le MODER
	masqueET = 0xFFFFFFFF - (0x03 << (2*pin));
	*emplacement &= masqueET;
	// On modifie le OTYPER
	emplacement += 0x04;
	// On modifie le OSPEEDR
	emplacement += 0x04;
	// On modifie le PUPDR
	emplacement += 0x04;
	masqueET = 0xFFFFFFFF - (1 << (2*pin));
	masqueOU = 0x02 << (2*pin);
	*emplacement &= masqueET;
	*emplacement |= masqueOU;
}

void PinOutInit(int adresseGPIO, int pin){

	// ********** POUR OUTPUT NOPULL **********

	int *emplacement = (int*) adresseGPIO;
	int masqueET = 0;
	int masqueOU = 0;
	// On modifie le MODER
	masqueET = 0xFFFFFFFF - (0x02 << (2*pin));
	masqueOU = 1 << (2*pin);
	*emplacement &= masqueET;
	*emplacement |= masqueOU;
	// On modifie le OTYPER
	emplacement += 0x04;
	masqueET = 0xFFFFFFFF - (1 << pin);
	*emplacement &= masqueET;
	// On modifie le OSPEEDR
	emplacement += 0x04;
	masqueET = 0xFFFFFFFF - (0x03 << (2*pin));
	*emplacement &= masqueET;
	// On modifie le PUPDR
	emplacement += 0x04;
	masqueET = 0xFFFFFFFF - (0x03 << (2*pin));
	*emplacement &= masqueET;
}

int pinInRead(int adresseGPIO, int pin){
	int *emplacement = (int*) (adresseGPIO + 0x10);
	int res = *emplacement >> pin;
	return res%2;
}

void pinOutWrite(int adresseGPIO, int pin, int val){
	int *emplacement = (int*) (adresseGPIO + 0x14);
	int aEcrire = 0;
	if (val){
		aEcrire = 1 << pin;
		*emplacement |= aEcrire;
	}
	else {
		aEcrire = 0xFFFFFFFF - (1 << pin);
		*emplacement &= aEcrire;
	}
}
