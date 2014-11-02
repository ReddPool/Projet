#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "fonction_gene_seq.h"

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

char* substMotif(char motif[], int nomSubs, FILE* Seqfile)
{
	char motif2[strlen(motif)];
	strcpy(motif2,motif);
	char subst[1],nuc[1];
	int i=0;
	int k=0;
	while(i<strlen(motif2))
	{
		int j=chanceSubst();
		subst[0]=genBases();
		nuc[0]=motif2[i];
		if (j && (subst[0] != nuc[0]) && k < nomSubs)
		{
			fprintf(Seqfile, "\n\tSubstitution du nucléotide numéro %i (%c) en %c",i+1, motif2[i],subst[0] );
			//printf("Substitution de %c en %c\n",motif2[i],subst[0] );
			motif2[i]=subst[0];
			k++;
			//printf("%s\n",motif2);
		}
		i++;
	}
	//printf("motif 2 : %s\n",motif2);
	return motif2;
}

//************************************************************************

void genSeq(int tailleSeq, int tailleMotif, int subst, char motif[], FILE* Seqfile, FILE* Fastafile)
{
	char* Seq = (char*)malloc(sizeof(char) * tailleSeq);
	int i=0;
	int pos;
	int occ=0;
	char motif2[120];
	
	

	fprintf(Seqfile, "Position(s) : ");

	if (tailleMotif<=tailleSeq) //Si la taille du motif est inférieure à la taille de la séquence
	{
		while(i < tailleSeq) //Tant qu'on est dans la séquence
		{
			int j = chanceMotif(); //Chance d'apparition du motif
			if(j && ((tailleSeq-i) > tailleMotif)) // Si le motif doit apparaitre et qu'il reste assez de nucléotides dans la séquence pour l'apparition du motif
			{
				//int substmotif = 0;
				int k = chanceSubst();
				pos=i+1;
				
				fprintf(Seqfile,"\n%i ",pos );
				if (k)//&& substmotif <= subst) // S'il y a une substitution et qu'on a pas encore atteint le nombre max de substitutions
				{
					strcpy(motif2,substMotif(motif,subst,Seqfile));
					strncat(Seq,motif2,tailleMotif);
					//substmotif++;
					//printf("%s\n", motif);
					i=i+tailleMotif;
					occ = occ +1;	
				}
				else
				{
					strncat(Seq,motif,tailleMotif);
					//printf("%s\n", motif);
					i=i+tailleMotif;
					occ = occ +1;
				}
				
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
//***********************************************************************

