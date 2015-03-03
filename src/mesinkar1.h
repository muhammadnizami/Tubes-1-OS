#ifndef MESINKAR1_H
#define MESINKAR1_H
#ifndef MARK
#define MARK '\0'
#endif

#include <stdbool.h>

/* definisi states */
char CC;
int mesinkar_i;

void START(const char* _pitaKar);
/* I.S. sembarang */
/* F.S. CC adalah karakter pertama pita */
/*		Jika CC==MARK, EOP menyala (true) */
/*		Jika CC!=MARK, EOP padam (false) */

void ADV(void);
/* I.S. CC!=MARK */
/* F.S. CC adalah karakter berikutnya dari CC pada I.S. */
/*		Jika CC==MARK, EOP menyala (true) */

bool EOP(void);
/* true jika CC==MARK */

#endif
