#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "fonction_lecture.h"


void LireChaine(char chaine[], int size) //Permet de lire une chaine de caractère rentrée par l'utilisateur
{
	fgets(chaine,size,stdin);
	chaine[strlen(chaine)-1] = '\0';
}

//***************************************************

int LireNombreEntier() //Permet de lire un nombre entier
{
	char chaine[64];
	fgets(chaine,64,stdin);

	return atoi(chaine);
}

//***********************************************************************
