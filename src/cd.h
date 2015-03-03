#ifndef cd_h
#define cd_h

#include <limits.h>

bool fileExists(const char * filepath);
//mengembalikan true bila ada berkas bernama filepath

int cd(char * to);
//I.S. ada working directory
//F.S. working directory berpindah ke to bila direktori tersebut ada
//	mengembalikan 0 bila berhasil
//	bila tidak, working directory tetap, return -1

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

char * homeDirToCurlyDash(char * dir, char * buf);
//I.S. dir berisi path
//F.S. dir disalin ke buf
//	apabila bagian depan dir merupakan home directory,
//	home directory disalin dengan ~

char * curlyDashToHomeDir(char * dir, char * buf);
//I.S. dir berisi suatu path
//F.S. jika buf == NULL, suatu variabel buffer yang statik akan berisi
//		path yang ~ diganti dengan home directory, dan return
//	jika buf != NULL, buf berisi dir yang ~ diganti home directory
//		return buf

#endif
