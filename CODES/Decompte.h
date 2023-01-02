#ifndef DEF_Decompte
#define DEF_Decompte
//----------


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "Initialisations.h"

// Les codes suivants correspondent aux segments allumés (1)
//ou éteints (0) pour former les nombres d'intérêts.

#define ZERO 111111
#define UN 110
#define DEUX 1101101
#define TROIS 1001111
#define QUATRE 1010110
#define CINQ 1011011
#define SIX 1111011
#define SEPT 1110
#define HUIT 1111111
#define NEUF 1011111

#define CPU_freq 216000000 /*Fréquence du CPU utilisé en Hertz.*/

#define NBCASDEMO 16

typedef struct feu{
	int id;
	int cpt_d;
	int cpt_u;
	int vert;	//Contient le booleen correspondant à l'allumage du feu vert.
	int jaune;	//De même pour le feu jaune.
	int rouge;	//De même pour le feu rouge.
}FEU;

int temporisation(FEU*, int, int[]);
int afficher(FEU*);
int patiente(int);

//----------
#endif