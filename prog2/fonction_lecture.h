#ifndef FONCTIONLECTURE
#define FONCTIONLECTURE

void LireChaine(char chaine[], int size);

//*******************************

int LireNombreEntier();

//********************************

int nombreSequences(FILE* nomFile);

//********************************

void strtoupper(char *str);

//********************************

void ecritureFasta(char* nom, char** sequences, int nombreSequences);

//********************************

void FastaVersTableau (char* Fastafile, char*** tableau);

//********************************

char* appendSeq (char* ptrTeteSeq, char* seqToAppend);

//********************************

void supprimeLastChar(char* string);



#endif /* end of include guard: FONCTIONLECTURE */
