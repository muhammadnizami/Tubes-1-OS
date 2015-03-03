#ifndef MESINKAR_C
#define MESINKAR_C
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include "mesinkar1.h"

/* definisi pita */
char* pitaKar;

void START(const char* _pitaKar){
/* I.S. sembarang */
/* F.S. CC adalah karakter pertama pita */
/*		Jika CC==MARK, EOP menyala (true) */
/*		Jika CC!=MARK, EOP padam (false) */
	pitaKar=_pitaKar;
	CC=pitaKar[0];
	mesinkar_i=0;
}

void ADV(void){
/* I.S. CC!=MARK */
/* F.S. CC adalah karakter berikutnya dari CC pada I.S. */
/*		Jika CC==MARK, EOP menyala (true) */
	mesinkar_i++;
	CC=pitaKar[mesinkar_i];
}

bool EOP(){
/* true jika CC==MARK */
	return(CC==MARK);
}

#endif
