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

void calculPSSM(float*** PSSM, char nuc, int i)
{
	//printf("%f\n", PSSM[i][0]);
	switch (nuc)
	{
		case 'a' : PSSM[i][0]++; break;
		case 't' : PSSM[i][1]++; break;
		case 'g' : PSSM[i][2]++; break;
		case 'c' : PSSM[i][3]++; break;
	}
}

//***********************************************************************

char* substMotif(char motif[], int nomSubs, FILE* Seqfile, float**** PSSM)
{
	char* motif2=(char*)malloc(sizeof(char)*(strlen(motif)+1));
	strcpy(motif2,motif);
	char subst,nuc;
	int i=0;
	int k=0;

	//InfoSubst* info=NULL;
	while(i<strlen(motif2))
	{
		int j=chanceSubst();
		subst=genBases();
		nuc=motif2[i];
		if (j && (subst != nuc) && k < nomSubs)
		{
			fprintf(Seqfile, "\n\tSubstitution du nucléotide numéro %i (%c) en %c",i+1, motif2[i],subst );
			//printf("Substitution de %c en %c\n",motif2[i],subst[0] );
			motif2[i]=subst;
			//calculPSSM(&PSSM,subst,i);
			switch (nuc)
			{
				case 'a' : PSSM[i][0]++; break;
				case 't' : PSSM[i][1]++; break;
				case 'g' : PSSM[i][2]++; break;
				case 'c' : PSSM[i][3]++; break;
			}
			k++;
			//printf("%s\n",motif2);
		}
		i++;
	}
	//printf("motif 2 : %s\n",motif2);
	//info = (InfoSubst*)malloc(sizeof(InfoSubst));
	//strcpy(motif,motif2);
	//info->_nbSub=k;
	motif2[i]='\0';
	return motif2;
}

//************************************************************************

char* genSeq(int tailleSeq, int tailleMotif, int subst, char* motif, FILE* Seqfile, float*** PSSM)
{	char* Seq = (char*) calloc(tailleSeq+1, sizeof(char));
	int i=0;
	int pos;
	int occ=0;
	char* motif2 = (char*) calloc(tailleMotif+1, sizeof(char));

	//PtrMotifs listeMotifs = NULL;
	//listeMotifs = (PtrMotifs)malloc(sizeof(Motifs));

	//PtrListeSeq listeSeq = NULL;

	fprintf(Seqfile, "Position(s) : ");

	if (tailleMotif<=tailleSeq) //Si la taille du motif est inférieure à la taille de la séquence
	{
		while(i < tailleSeq) //Tant qu'on est dans la séquence
		{

			int j = chanceMotif(); //Chance d'apparition du motif
			if(j && ((tailleSeq-i) > tailleMotif)) // Si le motif doit apparaitre et qu'il reste assez de nucléotides dans la séquence pour l'apparition du motif
			{
				//int substmotif = 0;
				pos=i+1;

				fprintf(Seqfile,"\n%i ",pos );
				//if (chanceSubst()) // S'il y a une substitution et qu'on a pas encore atteint le nombre max de substitutions
				//{
					strcpy(motif2,substMotif(motif, subst, Seqfile, &PSSM));
					strncat(Seq,motif2,tailleMotif);
					//printf("%i\n",(int) strlen(motif2) );
					//printf("%i\n",strlen(substMotif(motif,subst,Seqfile,PSSM)) );
					//printf("#\n");

					i=i+tailleMotif;
					occ = occ +1;
					//printf("%s\n",motif2 );
				//}
				/*else
				{
					strncat(Seq,motif,tailleMotif);
					printf("$\n");
					//printf("%s\n", motif);
					i=i+tailleMotif;
					occ = occ +1;
					//printf("%s\n", motif );
				}*/

			}
			else
			{
				//strcat(Seq,genBases());
				Seq[i]=genBases();
				i=i+1;
			}
		}
		//fprintf(Fastafile,"%s\n",Seq );
		fprintf(Seqfile, "\nOccurence(s) : %i\n\n", occ);
	}
	else
	{
		printf("Erreur, la taille de la séquence doit être plus grande que celle du motif\n");
	}
	//printf("%s",Seq);
	//listeMotifs->_listeSeq->next = NULL;
	Seq[i]='\0';
	return Seq;
}

//***********************************************************************
