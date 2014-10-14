#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define BUFFERMAX 50

char genBases() //Génération aléatoire de bases
{
	int Random= rand() % 3;
	char c;
	switch(Random)
	{
		case 0 : c = 'a';break;
		case 1 : c = 't';break;
		case 2 : c = 'g';break;
		case 3 : c = 'c';break;
	}
	return c;
}

//***********************************************************************

int chanceMotif() //Pourcentage d'apparition du motif dans la séquence
{
	int Random= rand() % 100;
	if (Random>5) 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//************************************************************************

void genSeq(int tailleSeq, int tailleMotif, char motif[], FILE* fichier, FILE* fichier2)
{
	char* Seq = (char*)malloc(sizeof(char) * tailleSeq);
	int i=0;
	int pos;
	int occ=0;

	

	fprintf(fichier, "Position(s) : ");

	if (tailleMotif<=tailleSeq)
	{
		while(i < tailleSeq)
		{
			int j = chanceMotif();
			if(j==1 && ((tailleSeq-i) > tailleMotif))
			{
				strncat(Seq,motif,tailleMotif);
				pos=i+1;
				i=i+tailleMotif;
				occ = occ +1;
				fprintf(fichier,"%i ",pos );
			}
			else
			{
				Seq[i]=genBases();
				i=i+1;
			}
			
		}
		fprintf(fichier2,"%s\n",Seq );
		fprintf(fichier, "\nOccurence(s) : %i\n\n", occ);
	}
	else
	{
		printf("Erreur, la taille de la séquence doit être plus grande que celle du motif\n");
	}
}

//***********************************************************************

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int tailleUtil,i;
	int choixTaille = 0;
	char taille[BUFFERMAX];
	printf("Quelle taille pour la séquence ?\n");
	do
	{
		printf(">");
		fgets(taille,BUFFERMAX,stdin);
		choixTaille = atoi(taille);
	} while(choixTaille ==0);

	printf("Taille définie : %i\n",choixTaille );
	char motif[] = "atcg";
	int tailleMotif=strlen(motif);
	printf("tailleMotif : %i\n",tailleMotif );

	FILE* fichier = NULL;
	FILE* fichier2 = NULL;

	fichier = fopen("test.txt","w");
	fprintf(fichier, "Motif : %s\n\n",motif);
	fichier2 = fopen("fasta.txt","w");

	char nombreSeq[BUFFERMAX];
	int choixSeq=0 ;
	printf("Combien de séquences voulez vous générer ?\n");
	do 
	{
		printf(">");
		fgets(nombreSeq,BUFFERMAX,stdin);
		choixSeq = atoi(nombreSeq);
	} while(choixSeq == 0);
	

	for (i = 0; i < choixSeq; ++i)
	{
		fprintf(fichier, "Seq %i\n", i+1);
		fprintf(fichier2, ">seq%i\n", i+1);
		genSeq(choixTaille,tailleMotif,motif,fichier,fichier2);
	}
	

	fclose(fichier);

	//printf("\nLe motif vaut %s\n", motif);

	return 0;
}