#include "Decompte.h"

int temporisation(FEU *pointFeu, int duree, int etats[]){
	int i,j;
	int premiere = 1;
	for (i = duree/10; i >= 0; i--){	// Ici, duree et 10 sont des int.
		pointFeu->cpt_d = etats[i];	// Donc pas de transtypage ou de floor recquis.
		for (j = (premiere ? (duree%10) : 9); j >= 0; j--){
			pointFeu->cpt_u = etats[j];
			afficher(pointFeu);
			patiente(1000);	//On attend une seconde.
		}
		premiere = 0;
	}
	return 0;
}

int afficher(FEU *pointFeu){
	int i, code_amenui_d = pointFeu->cpt_d, code_amenui_u = pointFeu->cpt_u;
	
	for (i = 0; i < 14; i++){
		PinOutWrite(monGPIOA, i, 0);
	}
	for (i = 0; i < 6; i++){
		PinOutWrite(monGPIOB, i, 1);
	}
	// LED initialement alimentée en inverse, en espérant
	// que cela ne les fasse pas griller.

	if ( (pointFeu->id == 1)||(pointFeu->id == 2) ){
		// feuP1 et feuP2.
		PinOutWrite(monGPIOB, 0, 0); // Dizaine P1
		PinOutWrite(monGPIOB, 1, 0); // Dizaine P2

		PinOutWrite(monGPIOB, 3, 0); // Unite P1
		PinOutWrite(monGPIOB, 4, 0); // Unite P2
	}
	else {
		// feuS.
		PinOutWrite(monGPIOB, 2, 0); // Dizaine S

		PinOutWrite(monGPIOB, 5, 0); // Unite S
	}

	for(i = 0; i < 7; i++){ /*Car un état fait 7 digits max.*/
		if(code_amenui_d%2 == 1){	//Test le digit de droite.
			PinOutWrite(monGPIOA, i, 1);
		}
		else {
			PinOutWrite(monGPIOA, i, 0);
		}
		if(code_amenui_u%2 == 1){	//Test le digit de droite.
			PinOutWrite(monGPIOA, 7+i, 1);
		}
		else {
			PinOutWrite(monGPIOA, 7+i, 0);
		}
		code_amenui_d = code_amenui_d/10;
		code_amenui_u = code_amenui_u/10;
		/* Sert à faire défiler le code vers la droite. */
	}
	return 0;
}

int patiente(int lapsMs){	/*Prend en argument une durée en ms.*/
	int i,N = lapsMs*CPU_freq/1000;
	for(i = 0; i < N; i++);	/*Répète la boucle sans action annexe.*/
	return 0;
}