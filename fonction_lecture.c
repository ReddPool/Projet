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

int nombreSequences(FILE* nomFile)
{
	int c;
	int nSeq = 0;
	//int c2 = '\0';

	while((c=fgetc(nomFile)) != EOF)
	{
		if(c=='>')
			nSeq++;
	}

	return nSeq;
}

//********************************************

void ecritureFasta(char* nom, char** sequences, int nombreSequences)
{
	int i;
	char fastaname[20];

	sprintf(fastaname,"%s.fasta",nom);
	FILE* Fastafile = NULL;
	Fastafile = fopen(fastaname,"w");

	if (Fastafile != NULL)
	{
		for(i = 0; i < nombreSequences; i++)
		{
			char* s = sequences[i];
			fprintf(Fastafile, ">seq%i\n%s\n", i+1, s);
		}
	}
	else
	{
		printf("Impossible d'ouvrir le fichier %s\n",fastaname );
	}
	fclose(Fastafile);
}

//**************************

//void calculPSSM(Motifs* tete)
