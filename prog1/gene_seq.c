#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "fonction_gene_seq.h"
#include "fonction_aleatoire.h"
#include "fonction_lecture.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int i;
	//char taille[BUFFERMAX];

	char motif[150] ; //Motif entré par l'utilisateur
	char nom[50]; //Nom du fichier que l'utilisateur veut générer
	char filename[50];
	char fastaname[50];
	int* PSSM = NULL;

	int subst = 0 ; //Nombre de substitutions max

	printf("Nom du fichier à générer :\n");
	LireChaine(nom,50);
	printf("Motif :\n");
	LireChaine(motif,150);
	int tailleMotif = strlen(motif);
	printf("tailleMotif : %i\n",tailleMotif );
	printf("Nombre de substitutions autorisées : \n");
	subst = LireNombreEntier();

	PSSM = (int*) calloc(tailleMotif * 4, sizeof(int));
	for(size_t hop = 0; hop < (tailleMotif * 4); hop++)
	{
		PSSM[hop] = 0.0;
	}
	//PSSM= *adr_PSSM;

	// initialisation des colonnes de la PSSM
	//for ( i = 0; i < tailleMotif; i++)
	//{
	//	PSSM[i] = (float*) calloc(4, sizeof(float));
	//}

	//Motifs* listeMotifs = NULL;


	FILE* Seqfile = NULL;
	//FILE* Fastafile = NULL;

	sprintf(filename,"%s.txt",nom);
	if((Seqfile = fopen(filename,"a")) != NULL){
		sprintf(fastaname,"%s.fasta",nom);
		fprintf(Seqfile, "Motif : %s\n\n",motif);


		int choixSeq=0;

		printf("Combien de séquences voulez vous générer ?\n");
		do
		{
			//printf(">");
			choixSeq = LireNombreEntier();
		} while(choixSeq == 0);

		char** sequences = malloc(choixSeq * sizeof(char*));
		for(int i = 0; i < choixSeq; i++)
		{
			sequences[i] = NULL;
		}

		for (i = 0; i < choixSeq; i++)
		{
			printf("%d\n", i);
			fprintf(Seqfile, "Seq %d\n", i+1);
			//fprintf(Fastafile, ">seq%i\n", i+1);
			int choixTaille = 200; //rand()%250+10;
			fprintf(Seqfile, "Taille : %d\n", choixTaille);
			sequences[i] = genSeq(choixTaille, tailleMotif,subst, motif, Seqfile, &PSSM);
		}

		ecritureFasta(nom,sequences,choixSeq);

		fclose(Seqfile);

		for ( i = 0; i < choixSeq; ++i)
		{
			free(sequences[i]);
		}

		return 0;
	}
	else
	{
		return 1;
	}
}
