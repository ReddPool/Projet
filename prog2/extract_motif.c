#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "fonction_lecture.h"


int main(int argc, char const *argv[])
{
	char nom[50];
	/*int motif=0;
	int subst=0;
	int fenetre=0;*/
	char fastaName[50];
	int nSeq;




	printf("Quel fichier voulez vous ouvrir ?\n");
	LireChaine(nom,50);
	//printf("%s\n",nom );

	/*printf("De quelle taille doit être le motif ?\n");
	motif=LireNombreEntier();

	printf("Quel est le nombre maximal de substitutions ?\n");
	subst=LireNombreEntier();

	printf("Combien de fenêtres voulez vous utiliser ?\n");
	fenetre=LireNombreEntier();*/

	FILE *fichier = NULL;
	sprintf(fastaName,"%s.fasta",nom);

	if((fichier = fopen(fastaName,"r")) != NULL)
	{
		nSeq = nombreSequences(fichier);
		printf("Nombre de séquences : %d\n",nSeq );
		fclose(fichier);
	}
	else
		puts("Erreur en ouverture du fichier");

	char** tableauSequences = (char**) calloc(nSeq, sizeof(char*));
	FastaVersTableau(fastaName, &tableauSequences);

	for (int i = 0; i < nSeq; ++i)
	{
		printf("%s\n",tableauSequences[i]);
	}

	return 0;
}
