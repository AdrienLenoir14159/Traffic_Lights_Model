#include "detection.h"

// Interversion due au fait que quand une voiture est détectée,
// c'est qu'elle coupe le laser, donc la LDR concernée a une
// Grosse résistance entre ses bornes, donc le pull down
// l'emporte et le bit lu est à 0...
// (Et inversement)

int detectionPresenceP1(void){
	if( PinInRead(monGPIOC, 0) ){
		return 0;
	}
	return 1;
}

int detectionPresenceP2(void){
	if( PinInRead(monGPIOC, 1) ){
		return 0;
	}
	return 1;
}

int detectionPresenceS(void){
	if( PinInRead(monGPIOC, 2) ){
		return 0;
	}
	return 1;
}
