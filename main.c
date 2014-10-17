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
	if (Random>2) 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//************************************************************************

void genSeq(int tailleSeq, int tailleMotif, char motif[], FILE* Seqfile, FILE* Fastafile)
{
	char* Seq = (char*)malloc(sizeof(char) * tailleSeq);
	int i=0;
	int pos;
	int occ=0;

	

	fprintf(Seqfile, "Position(s) : ");

	if (tailleMotif<=tailleSeq)
	{
		while(i < tailleSeq)
		{
			int j = chanceMotif();
			if(j && ((tailleSeq-i) > tailleMotif))
			{
				strncat(Seq,motif,tailleMotif);
				pos=i+1;
				i=i+tailleMotif;
				occ = occ +1;
				fprintf(Seqfile,"%i ",pos );
			}
			else
			{
				Seq[i]=genBases();
				i=i+1;
			}
			
		}
		Seq[i]='\0';
		fprintf(Fastafile,"%s\n",Seq );
		fprintf(Seqfile, "\nOccurence(s) : %i\n\n", occ);
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
	char taille[BUFFERMAX];
	
	//printf("Taille définie : %i\n",choixTaille );
	char motif[] = "atcg";
	int tailleMotif=strlen(motif);
	printf("tailleMotif : %i\n",tailleMotif );

	FILE* Seqfile = NULL;
	FILE* Fastafile = NULL;

	Seqfile = fopen("test.txt","w");
	fprintf(Seqfile, "Motif : %s\n\n",motif);
	Fastafile = fopen("fasta.txt","w");

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
		fprintf(Seqfile, "Seq %i\n", i+1);
		fprintf(Fastafile, ">seq%i\n", i+1);
		int choixTaille= rand()%250+10;
		fprintf(Seqfile, "Taille : %i\n", choixTaille);
		genSeq(choixTaille,tailleMotif,motif,Seqfile,Fastafile);
	}
	

	fclose(Seqfile);

	return 0;
}