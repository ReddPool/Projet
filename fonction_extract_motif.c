#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "fonction_extract_motif.h";

int nombreSequences(FILE* nomFile)
{
	int c;
	int nSeq = 0;
	int c2 = '\0';

	while((c=fgetc(nomFile)) != EOF)
	{
		if(c=='>')
			nSeq++;
	}

	return nSeq;
}

//********************************************

void lectureFasta(FILE* fichier, ptrListeSeq* ptrTete)
{
	FILE* fp = fichier;
	char* line = NULL;
}