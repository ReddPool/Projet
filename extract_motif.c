#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int nombreSequences(FILE* nomFile)
{
	int c;
	int nSeq = 0;
	int c2 = '\0';

	while((c=fgetc(nomFile)) != EOF)
	{
		if(c=='>')
			nSeq++;
	}

	return nSeq;
}

//********************************************

void LireChaine(char chaine[], int size) //Permet de lire une chaine de caractère rentrée par l'utilisateur
{
	fgets(chaine,size,stdin);
	chaine[strlen(chaine)-1] = '\0';
}

//*********************************************

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