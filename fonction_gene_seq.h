#ifndef FONCTIONGENESEQ
#define FONCTIONGENESEQ

typedef struct ListeSeq
{
	int _pos;
	int _nbSubst;
	char* _Motif_final;
	struct ListeSeq* next;
}ListeSeq;

typedef ListeSeq* PtrListeSeq;

typedef struct Motifs{
	char* _motif;
	struct ListeSeq* _listeSeq;
}Motifs;

typedef Motifs* PtrMotifs;

typedef struct InfoSubst
{
	char* _motif;
	int _nbSub;
	struct InfoSubst* next;
}InfoSubst;

//******************************

char genBases(); //Génération aléatoire de bases

//***********************

void LireChaine(char chaine[], int size); //Permet de lire une chaine de caractère rentrée par l'utilisateur

//***********************

int LireNombreEntier(); //Permet de lire un nombre entier

//***********************

int chanceMotif(); //Pourcentage d'apparition du motif dans la séquence

//***********************

int chanceSubst(); //Pourcentage de chance de substitution

//***********************

char* substMotif(char* motif, int nomSubs, FILE* Seqfile, float** PSSM); //Substitution dans le motif

//***********************

char* genSeq(int tailleSeq, int tailleMotif, int subst, char* motif, FILE* Seqfile, float** PSSM, int* nbMotifs); //Génération de la séquence et des fichiers

//***********************

void printFasta(char** tabSeq ,FILE* Fastafile, int i);

//***********************

void calculPSSM(float** PSSM, char nuc, int i);

//***********************

void freqPSSM(float** PSSM, int nbMotif, int tailleMotif); // Converti la PSSM en fréquence

#endif /* end of include guard: FONCTIONGENESEQ */
