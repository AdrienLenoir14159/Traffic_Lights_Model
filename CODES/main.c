#include "stm32f4xx.h"
#include "detection.h"
#include "LEDs.h"
#include "Decompte.h"
#include "Initialisations.h"

//~~~~~ NOTES: ~~~~~

// QUITE A TOUJOURS UTILISER SIMULTANEMENT 1 ET 2,
// AUTANT NE LES DIFFERENCIER QUE MATERIELLEMENT
// ET N'AVOIR QUE feuP ET feuS DANS LE CODE, AU LIEU
// D'AVOIR feuP1, feuP2 ET feuS.
// PROBLEME : COMPLICATION AVEC LES CAPTEURS QU'IL
// FAUT BIEN DIFFERENCIER.



int main(void){
	int nombreDeCasDemo = 0;
	int i;
	
	// Initialisations des constantes :
	
	int etats[10] = {ZERO, UN, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF};

	FEU feuP1, feuP2, feuS;
	feuP1.vert = 0;
	feuP1.jaune = 0;
	feuP1.rouge = 0;
	feuP2.vert = 0;
	feuP2.jaune = 0;
	feuP2.rouge = 0;
	feuS.vert = 0;
	feuS.jaune = 0;
	feuS.rouge = 0;
	feuP1.id = 1;
	feuP2.id = 2;
	feuS.id = 3;

	feuP1.cpt_u = 0; // Code tel que tout les segments soient éteints.
	feuP1.cpt_d = 0;
	feuP2.cpt_u = 0;
	feuP2.cpt_d = 0;
	feuS.cpt_u = 0;
	feuS.cpt_d = 0;
	
	// Fin d'initialisations des constantes.


	// Début de l'initialisation des ports GPIOs :
	PortClockInit(monGPIOA);
	PortClockInit(monGPIOB);
	PortClockInit(monGPIOC);
	// Fin de l'initialisation des ports GPIOs
	
	for (i = 0; i < 14; i++){	// Les 14 anodes d'afficheurs.
		PinOutInit(monGPIOA, i);
	}
	for (i = 0; i < 6; i++){	// Les 6 cathodes communes.
		PinOutInit(monGPIOB, i);
	}
	for (i = 6; i < 15; i++){	// Les 9 LEDs.
		PinOutInit(monGPIOB, i);
	}
	for (i = 0; i < 3; i++){	// Les 3 capteurs.
		PinInInit(monGPIOC, i);
	}

	while(nombreDeCasDemo < NBCASDEMO){ // Defini dans Decompte.h
		if ( !(feuP1.vert || feuP1.jaune || feuP1.rouge) ){
			// C'est à dire que l'on est à la première itération.
			// Donc les feux n'ont pas de "couleur précédante".
			// Ainsi il n'y a que trois/quatre cas:
			if (detectionPresenceP1() || detectionPresenceP2()){
				//Cas n°1 et 2 : Qu'importe la voie secondaire, P l'emporte.
				feuP1.vert = 1;
				feuP1.jaune = 0;
				feuP1.rouge = 0;

				feuP2.vert = 1;
				feuP2.jaune = 0;
				feuP2.rouge = 0;

				feuS.vert = 0;
				feuS.jaune = 0;
				feuS.rouge = 1;
				
				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);

				temporisation(&feuS, 30, etats);
			}
			else if ( (!detectionPresenceP1()) && (!detectionPresenceP2()) && detectionPresenceS() ){
				//Cas n°3 : S && !P
				feuP1.vert = 0;
				feuP1.jaune = 0;
				feuP1.rouge = 1;

				feuP2.vert = 0;
				feuP2.jaune = 0;
				feuP2.rouge = 1;
				
				feuS.vert = 1;
				feuS.jaune = 0;
				feuS.rouge = 0;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuP1, 30, etats);
			}
			else {	//Cas n°4 : Rien d'allumé.
				feuP1.vert = 0;
				feuP1.jaune = 0;
				feuP1.rouge = 0;

				feuP2.vert = 0;
				feuP2.jaune = 0;
				feuP2.rouge = 0;
				
				feuS.vert = 0;
				feuS.jaune = 0;
				feuS.rouge = 0;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				// Pas de temporisation à ajouter.
			}
		} 
		else { //Sinon, on a à faire aux 9 cas décrits dans le rapport.
			if( (detectionPresenceP1() || detectionPresenceP2()) && (feuP1.vert || feuP2.vert) && (feuS.rouge) ){
				feuP1.vert = 1;
				feuP1.jaune = 0;
				feuP1.rouge = 0;

				feuP2.vert = 1;
				feuP2.jaune = 0;
				feuP2.rouge = 0;
				
				feuS.vert = 0;
				feuS.jaune = 0;
				feuS.rouge = 1;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuS, 30, etats);
			}
			else if ( (detectionPresenceP1() || detectionPresenceP2()) && (feuP1.rouge || feuP2.rouge) && (feuS.vert) ){
				feuP1.vert = 0;
				feuP1.jaune = 0;
				feuP1.rouge = 1;

				feuP2.vert = 0;
				feuP2.jaune = 0;
				feuP2.rouge = 1;
				
				feuS.vert = 0;
				feuS.jaune = 1;
				feuS.rouge = 0;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuP1, 5, etats);
			}
			else if ( (detectionPresenceP1() || detectionPresenceP2()) && (feuP1.rouge || feuP2.rouge) && (feuS.jaune) ){
				feuP1.vert = 1;
				feuP1.jaune = 0;
				feuP1.rouge = 0;

				feuP2.vert = 1;
				feuP2.jaune = 0;
				feuP2.rouge = 0;
				
				feuS.vert = 0;
				feuS.jaune = 0;
				feuS.rouge = 1;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuS, 30, etats);
			}
			else if ( !(detectionPresenceP1() || detectionPresenceP2()) && (feuP1.vert || feuP2.vert) && detectionPresenceS() && (feuS.rouge) ){
				feuP1.vert = 0;
				feuP1.jaune = 1;
				feuP1.rouge = 0;

				feuP2.vert = 0;
				feuP2.jaune = 1;
				feuP2.rouge = 0;
				
				feuS.vert = 0;
				feuS.jaune = 0;
				feuS.rouge = 1;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuS, 5, etats);
			}
			else if ( !(detectionPresenceP1() || detectionPresenceP2()) && (feuP1.rouge || feuP2.rouge) && detectionPresenceS() && (feuS.vert) ){
				feuP1.vert = 0;
				feuP1.jaune = 0;
				feuP1.rouge = 1;

				feuP2.vert = 0;
				feuP2.jaune = 0;
				feuP2.rouge = 1;
				
				feuS.vert = 1;
				feuS.jaune = 0;
				feuS.rouge = 0;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuP1, 30, etats);
			}
			else if ( !(detectionPresenceP1() || detectionPresenceP2()) && (feuP1.jaune || feuP2.jaune) && detectionPresenceS() && (feuS.rouge) ){
				feuP1.vert = 0;
				feuP1.jaune = 0;
				feuP1.rouge = 1;

				feuP2.vert = 0;
				feuP2.jaune = 0;
				feuP2.rouge = 1;
				
				feuS.vert = 1;
				feuS.jaune = 0;
				feuS.rouge = 0;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuP1, 30, etats);
			}
			else if ( !(detectionPresenceP1() || detectionPresenceP2()) && (feuP1.vert || feuP2.vert) && !detectionPresenceS() && (feuS.rouge) ){
				feuP1.vert = 1;
				feuP1.jaune = 0;
				feuP1.rouge = 0;

				feuP2.vert = 1;
				feuP2.jaune = 0;
				feuP2.rouge = 0;
				
				feuS.vert = 0;
				feuS.jaune = 0;
				feuS.rouge = 1;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuS, 30, etats);
			}
			else if ( !(detectionPresenceP1() || detectionPresenceP2()) && (feuP1.rouge || feuP2.rouge) && !detectionPresenceS() && (feuS.vert) ){
				feuP1.vert = 1;
				feuP1.jaune = 0;
				feuP1.rouge = 0;

				feuP2.vert = 1;
				feuP2.jaune = 0;
				feuP2.rouge = 0;
				
				feuS.vert = 0;
				feuS.jaune = 0;
				feuS.rouge = 1;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuS, 5, etats);
			}
			else if ( !(detectionPresenceP1() || detectionPresenceP2()) && (feuP1.rouge || feuP2.rouge) && !detectionPresenceS() && (feuS.jaune) ){
				feuP1.vert = 1;
				feuP1.jaune = 0;
				feuP1.rouge = 0;

				feuP2.vert = 1;
				feuP2.jaune = 0;
				feuP2.rouge = 0;
				
				feuS.vert = 0;
				feuS.jaune = 0;
				feuS.rouge = 1;

				allumerLEDs(&feuP1);
				allumerLEDs(&feuP2);
				allumerLEDs(&feuS);
				
				temporisation(&feuS, 30, etats);
			}
		}
		nombreDeCasDemo++;
	}
	return 0;
}