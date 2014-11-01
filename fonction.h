#define BUFFERMAX 50

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

char* substMotif(char motif[], FILE* Seqfile); //Substitution dans le motif

//***********************

void genSeq(int tailleSeq, int tailleMotif, int subst, char motif[], FILE* Seqfile, FILE* Fastafile) //Génération de la séquence et des fichiers


