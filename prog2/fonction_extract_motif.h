#ifndef LISTESEQ
#define LISTESEQ

typedef struct listeSeq
{
	int id;
	char* ptrSeq;
	struct listeSeq* next;

}listeSeq;

typedef listeSeq* ptrListeSeq;

#endif /* end of include guard: LISTESEQ */
