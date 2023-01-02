#include "LEDs.h"

int allumerLEDs(FEU *pointFeu){
	// 3 feux de trois LEDs : 9 GPIOs employés.
	if( ( (pointFeu->id == 1) || (pointFeu->id == 2) ) && pointFeu->vert ){
		PinOutWrite(monGPIOB, 6, 1);
		PinOutWrite(monGPIOB, 7, 0);
		PinOutWrite(monGPIOB, 8, 0);

		PinOutWrite(monGPIOB, 9, 1);
		PinOutWrite(monGPIOB, 10, 0);
		PinOutWrite(monGPIOB, 11, 0);

		PinOutWrite(monGPIOB, 12, 0);
		PinOutWrite(monGPIOB, 13, 0);
		PinOutWrite(monGPIOB, 14, 0);
	}
	else if ( ( (pointFeu->id == 1) || (pointFeu->id == 2) ) && pointFeu->jaune ){
		PinOutWrite(monGPIOB, 6, 0);
		PinOutWrite(monGPIOB, 7, 1);
		PinOutWrite(monGPIOB, 8, 0);

		PinOutWrite(monGPIOB, 9, 0);
		PinOutWrite(monGPIOB, 10, 1);
		PinOutWrite(monGPIOB, 11, 0);

		PinOutWrite(monGPIOB, 12, 0);
		PinOutWrite(monGPIOB, 13, 0);
		PinOutWrite(monGPIOB, 14, 0);
	}
	else if ( ( (pointFeu->id == 1) || (pointFeu->id == 2) ) && pointFeu->rouge ){	//pointFeu->rouge est forcément à 1 dans ce cas restant.
		PinOutWrite(monGPIOB, 6, 0);
		PinOutWrite(monGPIOB, 7, 0);
		PinOutWrite(monGPIOB, 8, 1);

		PinOutWrite(monGPIOB, 9, 0);
		PinOutWrite(monGPIOB, 10, 0);
		PinOutWrite(monGPIOB, 11, 1);

		PinOutWrite(monGPIOB, 12, 0);
		PinOutWrite(monGPIOB, 13, 0);
		PinOutWrite(monGPIOB, 14, 0);
	}
	else if( (pointFeu->id == 3) && pointFeu->vert ){
		PinOutWrite(monGPIOB, 6, 0);
		PinOutWrite(monGPIOB, 7, 0);
		PinOutWrite(monGPIOB, 8, 0);

		PinOutWrite(monGPIOB, 9, 0);
		PinOutWrite(monGPIOB, 10, 0);
		PinOutWrite(monGPIOB, 11, 0);

		PinOutWrite(monGPIOB, 12, 1);
		PinOutWrite(monGPIOB, 13, 0);
		PinOutWrite(monGPIOB, 14, 0);
	}
	else if ( (pointFeu->id == 3) && pointFeu->jaune ){
		PinOutWrite(monGPIOB, 6, 0);
		PinOutWrite(monGPIOB, 7, 0);
		PinOutWrite(monGPIOB, 8, 0);

		PinOutWrite(monGPIOB, 9, 0);
		PinOutWrite(monGPIOB, 10, 0);
		PinOutWrite(monGPIOB, 11, 0);

		PinOutWrite(monGPIOB, 12, 0);
		PinOutWrite(monGPIOB, 13, 1);
		PinOutWrite(monGPIOB, 14, 0);
	}
	else if ( (pointFeu->id == 3) && pointFeu->rouge ){
		PinOutWrite(monGPIOB, 6, 0);
		PinOutWrite(monGPIOB, 7, 0);
		PinOutWrite(monGPIOB, 8, 0);

		PinOutWrite(monGPIOB, 9, 0);
		PinOutWrite(monGPIOB, 10, 0);
		PinOutWrite(monGPIOB, 11, 0);

		PinOutWrite(monGPIOB, 12, 0);
		PinOutWrite(monGPIOB, 13, 0);
		PinOutWrite(monGPIOB, 14, 1);
	}
	else {
		return 0; // Anomalie
	}
}
