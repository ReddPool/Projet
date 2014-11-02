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

	int tailleUtil,i;
	//char taille[BUFFERMAX];
	
	char motif[150] ; //Motif entré par l'utilisateur
	char nom[20]; //Nom du fichier que l'utilisateur veut générer
	char filename[20];
	char fastaname[20];
	int subst = 0 ; //Nombre de substitutions max

	printf("Nom du fichier à générer :\n");
	LireChaine(nom,20);
	printf("Motif :\n");
	LireChaine(motif,150);
	int tailleMotif=strlen(motif);
	printf("tailleMotif : %i\n",tailleMotif );
	printf("Nombre de substitutions autorisées : \n");
	subst = LireNombreEntier();


	FILE* Seqfile = NULL;
	FILE* Fastafile = NULL;

	sprintf(filename,"%s.txt",nom);
	Seqfile = fopen(filename,"w");
	sprintf(fastaname,"%s.fasta",nom);
	fprintf(Seqfile, "Motif : %s\n\n",motif);
	Fastafile = fopen(fastaname,"w");

	//char nombreSeq[BUFFERMAX];
	int choixSeq=0 ;
	printf("Combien de séquences voulez vous générer ?\n");
	do 
	{
		printf(">");
		choixSeq = LireNombreEntier();
	} while(choixSeq == 0);
	

	for (i = 0; i < choixSeq; ++i)
	{
		fprintf(Seqfile, "Seq %i\n", i+1);
		fprintf(Fastafile, ">seq%i\n", i+1);
		int choixTaille= rand()%250+10;
		fprintf(Seqfile, "Taille : %i\n", choixTaille);
		genSeq(choixTaille,tailleMotif,subst,motif,Seqfile,Fastafile);
	}
	

	fclose(Seqfile);

	return 0;
}