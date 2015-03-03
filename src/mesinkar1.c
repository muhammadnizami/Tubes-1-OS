#ifndef MESINKAR_C
#define MESINKAR_C
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include "mesinkar1.h"

/* definisi pita */
static char Pita_karakter[63] = "pitakar.txt";
static FILE * FILEKU;
static int retval;

void START(char* namafile){
/* I.S. sembarang */
/* F.S. CC adalah karakter pertama pita */
/*		Jika CC==MARK, EOP menyala (true) */
/*		Jika CC!=MARK, EOP padam (false) */
	if(namafile[0]=='-' && namafile[1]=='\0')
		FILEKU = stdin;
	else FILEKU = fopen(namafile,"r");
	retval = fscanf(FILEKU,"%c",&CC);
}

void ADV(void){
/* I.S. CC!=MARK */
/* F.S. CC adalah karakter berikutnya dari CC pada I.S. */
/*		Jika CC==MARK, EOP menyala (true) */
	retval = fscanf(FILEKU,"%c",&CC);
	if(CC==MARK) {
		if (FILEKU!=stdin)
			fclose(FILEKU);
	}
}

bool EOP(){
/* true jika CC==MARK */
	return(CC==MARK);
}

#endif