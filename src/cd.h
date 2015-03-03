#ifndef cd_h
#define cd_h

#include <limits.h>

bool fileExists(const char * filepath);
//mengembalikan true bila ada berkas bernama filepath

bool dirExists(const char * dir);
//mengembalikan true bila ada direktori dir

char * cd(char * from, char * to);
//I.S. dirExists(from)
//F.S. from berpindah ke to bila direktori tersebut ada
//	mengembalikan from bila berhasil
//	bila tidak, from tetap, return null pointer

char * getHomeDir(char * dst);
//I.S. dst berisi cukup ukuran, atau null
//F.S. bila dst tidak null, dst berisi home directory
//	mengembalikan dst
//	bila dst null, home directory disimpan di variabel statik
//	mengembalikan alamat variabel statik tersebut

void printDir(char * dir);
//I.S. dir berisi path
//F.S. dir dicetak ke layar. tidak ada newline
//	apabila bagian depan dir merupakan home directory,
//	home directory ditampilkan dengan ~

#endif
