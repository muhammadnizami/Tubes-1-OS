#ifndef MESINKATA1_H
#define MESINKATA1_H
#include <math.h>

/* { ***** Mesin lain yang dipakai ***** } */
//use MESINKAR;
#include "mesinkar1.h"
/* { ***** Konstanta ***** } */
#ifndef MARK
#define MARK '\0'
#endif

#ifndef BLANK
#define BLANK ' '
#endif

#define NMax 50 //{ jumlah maksimum karakter suatu kata }

/* { ***** Definisi Type Kata ***** } */
typedef struct{
	char TabKata[NMax + 1];
	int Length;
} Kata;

/* { TabKata adalah tempat penampung/container kata, Length menyatakan panjangnya kata }
{ ***** Definisi State Mesin Kata ***** } */
bool EndKata; //{ penanda akhir akuisisi kata }
Kata CKata; //{ kata yang sudah diakuisisi dan akan diproses }
enum {stat_arg,stat_opr} status; //{status mesin kata, apakah sedang membaca operator atau argumen}

/* { ***** Primitif-Primitif Mesin Kata ***** } */
void Ignore_Blank();
/* { Mengabaikan satu atau beberapa BLANK }
{ I.S. : CC sembarang }
{ F.S. : CC ≠ BLANK atau CC = MARK } */

void STARTKATA(const char* pitaKar);
/* { I.S. : CC sembarang }
{ F.S. : EndKata = true, dan CC = Mark; }
{        atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
		 CC karakter pertama sesudah karakter terakhir kata } */
		 
void ADVKATA();
/* { I.S. : EndKata = false; CC adalah karakter sesudah karakter terakhir
           dari kata yg sudah diakuisisi } { F.S. : Jika CC = MARK, maka EndKata = true
		   atau EndKata = false, CKata adalah kata terakhir yang sudah diakuisisi;
		   CC karakter pertama sesudah karakter terakhir kata } */
		   
void SalinKata();
/* { Mengakuisisi kata, menyimpan dalam CKata }
{ I.S. : CC adalah karakter pertama dari kata }
{ F.S. : CKata berisi kata yang sudah diakuisisi, jika karakternya melebihi
           NMax, sisa "kata" dibuang; CC = BLANK atau CC = MARK; CC adalah
           karakter sesudah karakter terakhir yang diakuisisi } */
//terdapat dua mode pembacaan kata
//1. dari tanda kutip hingga tanda kutip
//2. dari spasi hingga spasi, di tengahnya bisa ada escape sequence (belum diimplementasi)
		 
/* { ***** Operasi Lain ***** } */
bool IsKataSama (Kata K1, Kata K2);
/* { Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama
 dan urutan karakter yang menyusun kata juga sama } */

void PrintKata(Kata K);
//{mengeprint kata}

int convertToInt(char C);
//{convert ke integer}

int kataToInt(Kata K);
/* I.S. Kata berisi kumpulan karakter 0 sampai 9 */
/* F.S. Kata diubah menjadi integer */

void StrFromKata(char * dest, Kata K);
/* I.S. dest berukuran cukup, K ada */
/* F.S. dest berisi string dari Kata */
 #endif
