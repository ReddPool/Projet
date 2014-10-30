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

void LireChaine(char chaine[], int size) //Permet de lire une chaine de caractère rentrée par l'utilisateur
{
	fgets(chaine,size,stdin);
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

int chanceSubst() //Pourcentage de chance de substitution
{
	int Random= rand() % 100;
	if (Random>50) 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//************************************************

char* substMotif(char motif[], FILE* Seqfile)
{
	char motif2[strlen(motif)];
	strcpy(motif2,motif);
	char subst[1],nuc[1];
	int i=0;
	while(i<strlen(motif2))
	{
		int j=chanceSubst();
		subst[0]=genBases();
		nuc[0]=motif2[i];
		if (j && (subst[0] != nuc[0]) )
		{
			fprintf(Seqfile, "\nSubstitution de %c en %c", motif2[i],subst[0] );
			printf("Substitution de %c en %c\n",motif2[i],subst[0] );
			motif2[i]=subst[0];
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
				int substmotif = 0;
				int k = chanceSubst();
				pos=i+1;
				
				fprintf(Seqfile,"\n%i ",pos );
				if (k && substmotif <= subst) // S'il y a une substitution et qu'on a pas encore atteint le nombre max de substitutions
				{
					strcpy(motif2,substMotif(motif,Seqfile));
					strncat(Seq,motif2,tailleMotif);
					substmotif++;
					printf("%s\n", motif);
					i=i+tailleMotif;
					occ = occ +1;	
				}
				else
				{
					strncat(Seq,motif,tailleMotif);
					printf("%s\n", motif);
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

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int tailleUtil,i;
	char taille[BUFFERMAX];
	
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

	char nombreSeq[BUFFERMAX];
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