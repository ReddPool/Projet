#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void genSeq(int tailleSeq, int tailleMotif)
{
	char Seq[tailleSeq];
	int i;
	if (tailleMotif<tailleSeq)
	{
		for (i = 0; i < tailleSeq; ++i)
		{
			Seq[i]=genBases();
			printf("%c", Seq[i]);
		}
	}
	else
	{
		printf("Erreur, la taille de la séquence doit être plus grande que celle du motif\n");
	}

}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int tailleUtil;
	printf("Quelle taille pour la séquence ?\n");
	scanf("%i",&tailleUtil);
	printf("Taille définie : %i\n",tailleUtil );
	//char a;
	//a=genBases();
	//printf("%c\n", a);
	genSeq(tailleUtil,4);
	printf("\n");
	char motif[] = "atcg";
	printf("Le motif vaut %s\n", motif);
	printf("%i\n", chanceMotif() );
	return 0;
}