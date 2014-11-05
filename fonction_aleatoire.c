#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "fonction_aleatoire.h"

int chanceMotif() //Pourcentage d'apparition du motif dans la séquence
{
	int Random= rand() % 100+1;
	if (Random>2) 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int chanceSubst() //Pourcentage de chance de substitution
{
	int Random= rand() % 100;
	if (Random>10) 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//************************************************