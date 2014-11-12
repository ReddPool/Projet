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
	char nom[20]; //Nom du fichier que l'utilisateur veut générer
	char filename[20];
	char fastaname[20];
	float** PSSM = NULL;

	int subst = 0 ; //Nombre de substitutions max
	int nbMotifs = 0; // Nombre de Motifs au total (nécessaire pour le calcul de la PSSM)

	printf("Nom du fichier à générer :\n");
	LireChaine(nom,20);
	printf("Motif :\n");
	LireChaine(motif,150);
	int tailleMotif = strlen(motif);
	printf("tailleMotif : %i\n",tailleMotif );
	printf("Nombre de substitutions autorisées : \n");
	subst = LireNombreEntier();

	/*
	PSSM = (int*) calloc(tailleMotif * 4, sizeof(int));
	for(size_t hop = 0; hop < (tailleMotif * 4); hop++)
	{
		PSSM[hop] = 0.0;
	}
	*/

	PSSM = (float**) calloc(tailleMotif, sizeof(float*));
	for(size_t hop = 0; hop < tailleMotif; hop++)
	{
		PSSM[hop] = (float*) calloc(4, sizeof(float));
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
	if((Seqfile = fopen(filename,"w+")) != NULL){
		sprintf(fastaname,"%s.fasta",nom);
		fprintf(Seqfile, "Motif : %s\n\n",motif);


		int choixSeq=0;

		printf("Combien de séquences voulez vous générer ?\n");
		do
		{
			//printf(">");
			choixSeq = LireNombreEntier();
		} while(choixSeq == 0);

		char** sequences = (char**)malloc(sizeof(char*) * choixSeq);
		for(int i = 0; i < choixSeq; i++)
		{
			sequences[i] = NULL;
		}

		for (i = 0; i < choixSeq; i++)
		{
			//fprintf(Seqfile, "Seq %d\n", i+1);
			//fprintf(Fastafile, ">seq%i\n", i+1);
			int choixTaille = 200; //rand()%250+10;
			fprintf(Seqfile, "Taille : %d\n", choixTaille);
			sequences[i] = genSeq(choixTaille, tailleMotif, subst, motif, Seqfile, PSSM, &nbMotifs);
		}

		// Permet de donnée la fréquence de l'apparition des bases à la PSSM
		freqPSSM(PSSM, nbMotifs, tailleMotif);


		// Affichage de la PSSM
		for (int i = 0; i < tailleMotif; i++)
		{
			printf("\nPosition %d\n", i);
			printf("A : %f\n", PSSM[i][0]);
			printf("T : %f\n", PSSM[i][1]);
			printf("G : %f\n", PSSM[i][2]);
			printf("C : %f\n", PSSM[i][3]);
			
		}

		//ecritureFasta(nom,sequences,choixSeq);

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
