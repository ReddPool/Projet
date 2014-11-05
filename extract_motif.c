#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "fonction_lecture.h"


int main(int argc, char const *argv[])
{
	//char nom[30];

	//printf("Quel fichier voulez vous ouvrir ?\n");

	FILE *fichier = (fopen("test1.fasta","r"));

	if(fichier != NULL)
	{
		int nSeq = nombreSequences(fichier);

		printf("Nombre de lignes : %d\n",nSeq );

		fclose(fichier);
	}
	else
		puts("Erreur en ouverture du fichier");

	return 0;
}