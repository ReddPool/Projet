#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "fonction_lecture.h"

void strtoupper(char *str)
{
    for ( ; *str ; str++)
        *str = toupper(*str);
}

//***********************

void LireChaine(char chaine[], int size) //Permet de lire une chaine de caractère rentrée par l'utilisateur
{
	fgets(chaine,size,stdin);
	strtoupper(chaine);
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

void supprimeLastChar(char* string)
{
	char* ptr;
	if( (ptr = strchr(string, '\n')) != NULL) //Remplace les retours à la ligne par des \0
		*ptr = '\0';
}

//*************************

char* appendSeq (char* ptrTeteSeq, char* seqToAppend)
{
	char* newSeq; // pointera vers la nouvelle zone de mémoire à la bonne taille
	//char* oldSeq = ptrTeteSeq; //
	supprimeLastChar(seqToAppend);
	int tailleNewSeq = ( (strcmp(ptrTeteSeq, "\0") != 0) ? strlen(ptrTeteSeq) : 0) + strlen(seqToAppend);
	if((newSeq = calloc((tailleNewSeq + 1), sizeof(char))) != NULL)
	{
		strncat(newSeq, ptrTeteSeq, tailleNewSeq);
		strncat(newSeq, seqToAppend, tailleNewSeq);
	}
	else
	{
		printf("Erreur d'allocation mémoire : appendSeq()");
	}
	//free(oldSeq);
	return newSeq;
}

//************************

void FastaVersTableau (char* fastaName, char*** tableau)
{
	FILE* fp = NULL;
	char* line = NULL;
	size_t count = 0;
	char** seqCourrante = NULL;
	
	if ((fp=fopen(fastaName,"r")) == NULL)
	{
		printf("Impossible d'ouvrir le fichier\n");
	}
	else
	{
		while((getline(&line, &count, fp)) != -1)
		{
			if(line[0] == '>') //s'il s'agit d'une nouvelle séquence
			{
				if(seqCourrante != NULL)
				{
					seqCourrante++; //on passe à la séquence suivante dans le tableau
				}
				else //s'il s'agit de la première séquence
				{
					seqCourrante = *tableau;
				}
				// création du pointeur de la chaine de charactères
				*seqCourrante = calloc(1, sizeof(char));
			}
			else // ajout de la séquence
			{
				supprimeLastChar(line); // supprime les retours à la ligne
				*seqCourrante = appendSeq(*seqCourrante, line);
			}
		}
	}
	free(line);
	fclose(fp);
}



//***********************************

//void calculPSSM(Motifs* tete)
