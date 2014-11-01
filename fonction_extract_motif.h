int nombreSequences(FILE* nomFile);

//***********************************

typedef struct listeSeq
{
	int id;
	char* ptrSeq;
	struct listeSeq* next;

}listeSeq;

typedef liste_seq ptrListeSeq;