#ifndef eksekusi_h
#define eksekusi_h

bool isExecutable(const char * path);
//mengembalikan true bila path menunjuk berkas eksekutabel

void eksekusi(const char * path, char * argv[]);
//I.S. isExecutable(path)
//F.S. terbentuk proses anak yang menjalankan path

void eksekusi(const char * path, char * argv[], int in, int out, bool bergantian);
//I.S. isExecutable(path)
//F.S. terbentuk proses anak yang menjalankan path
//	dengan stdin dan stdout diredirect ke pid_in dan pid_out
//	bila bergantian false, proses anak dilakukan bersama proses induk

#endif
