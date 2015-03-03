#ifndef MESINKATA1_C
#define MESINKATA1_C
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include "mesinkata1.h"

/* { ***** Mesin lain yang dipakai ***** } */
//use MESINKAR

/* { TabKata adalah tempat penampung/container kata, Length menyatakan panjangnya kata }

/* { ***** Primitif-Primitif Mesin Kata ***** } */
void Ignore_Blank(){
/* { Mengabaikan satu atau beberapa BLANK }
{ I.S. : CC sembarang }
{ F.S. : CC ≠ BLANK atau CC = MARK } */
	while (((CC == BLANK)||(CC == '\n')) && (CC != MARK)) {
		ADV();
	}
}
void STARTKATA(const char* pitaKar){
/* { I.S. : CC sembarang }
{ F.S. : EndKata = true, dan CC = Mark; }
{        atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
		 CC karakter pertama sesudah karakter terakhir kata } */
	START(pitaKar);
	status = stat_arg;
	Ignore_Blank();
	if (CC == MARK) {
		EndKata = true;
	} else {
		EndKata = false;
		SalinKata();
	}
}

void ADVKATA(){
/* { I.S. : EndKata = false; CC adalah karakter sesudah karakter terakhir
     dari kata yg sudah diakuisisi } { F.S. : Jika CC = MARK, maka EndKata = true
     atau EndKata = false, CKata adalah kata terakhir yang sudah diakuisisi;
     CC karakter pertama sesudah karakter terakhir kata } */
	Ignore_Blank();
	if(CC == MARK){
		EndKata = true;
	} else {
		SalinKata();
	}
}

void SalinKata_kutip(int * tabkata_index);
//menambahkan karakter yang dibaca di antara kutip ke TabKata[tabkata_index] dst
//tabkata_index sebesar panjang sekarang
//CC berada pada tanda kutip

void SalinKata_esc(int * tabkata_index);
//menambahkan karakter yang dibaca setelah '\' ke TabKata[tabkata_index] dst
//tabkata_index sebesar panjang sekarang
//CC berada pada karakter terakhir yang terpengaruh escape sequence
//escape sequence yang ditangani: \",\\,\<,\|,\ ,

void SalinKata(){
/* { Mengakuisisi kata, menyimpan dalam CKata }
{ I.S. : CC adalah karakter pertama dari kata }
{ F.S. : CKata berisi kata yang sudah diakuisisi, jika karakternya melebihi
           NMax, sisa "kata" dibuang; CC = BLANK atau CC = MARK; CC adalah
           karakter sesudah karakter terakhir yang diakuisisi } */
//terdapat dua status khusus pembacaan kata
//1. dari tanda kutip hingga tanda kutip
//2. escape sequence (belum diimplementasi)
	int i = 1;
	if (CC == '|' || CC == '<' || CC == '>') 
		status = stat_opr;
	else	status = stat_arg;
	
	for(;;) {
		switch(CC){
		case '\\':
			SalinKata_esc(&i);
			break;
		case '\"':
			SalinKata_kutip(&i);
			break;
		default:
			CKata.TabKata[i] = CC;
		}
		ADV();
		if (status == stat_arg && (CC == '|' || CC == '<' || CC == '>') ){
			break;
		} else if (status == stat_opr && !(CC == '|' || CC == '<' || CC == '>') ){
			break;
		} else if((CC == MARK) || (CC == BLANK) || (CC == '\n')){
			break;
		} else {
			i++;
		}
	}	
	CKata.Length = i;
}

void SalinKata_esc(int * tabkata_index){
	//implementasikan escape sequence di sini
	ADV();
	switch(CC){
	
	//gunakan case untuk yang lain

	default:	//termasuk \",\\,\<,\ ,\|
			//escape sequence yang belum diimplementasikan akan dianggap huruf biasa
		CKata.TabKata[*tabkata_index] = CC;
	}
}

void SalinKata_kutip(int * tabkata_index){
	bool tambahanbaris = false;
	for(ADV();CC!='\"';ADV()) {
		CKata.TabKata[*tabkata_index] = CC;
		(*tabkata_index)++;
	}
	(*tabkata_index)--;
}

/* { ***** Operasi Lain ***** } */
bool IsKataSama (Kata K1, Kata K2){
/* { Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama
 dan urutan karakter yang menyusun kata juga sama } */
	if(K1.Length != K2.Length){
		return false;
	} else {
		int i = 1;
		bool sama = true;
		while(sama && (i<= K1.Length)){
			if(K1.TabKata[i] != K2.TabKata[i]){
				sama = false;
			}
			i++;
		}
		return sama;
	}
 
 }
 
void PrintKata(Kata K){
	int i = 1;
	while (i <= K.Length){
		printf("%c",K.TabKata[i]);
		i++;
	}
	printf(" ");
 }
 
int convertToInt(char C){
	switch(C){
		case '0': return 0; break;
		case '1': return 1; break;
		case '2': return 2; break;
		case '3': return 3; break;
		case '4': return 4; break;
		case '5': return 5; break;
		case '6': return 6; break;
		case '7': return 7; break;
		case '8': return 8; break;
		case '9': return 9; break;
	}
}

int kataToInt(Kata K){
/* I.S. Kata berisi kumpulan karakter 0 sampai 9 */
/* F.S. Kata diubah menjadi integer */
	int i = 1;
	int s = 0;
	int pgkt;
	while(i<=K.Length){
		pgkt = pow(10,K.Length - i);
		s += convertToInt(K.TabKata[i]) * pgkt;
		i++;
	}
	return s;
}

void StrFromKata(char * dst, Kata K){
/* I.S. dest berukuran cukup, K ada */
/* F.S. dest berisi string dari Kata */
	int i;
	for (i=1;i<=K.Length;i++){
		dst[i-1]=K.TabKata[i];
	}
	dst[i-1]='\0';
}
 #endif
