#ifndef eksekusi_h
#define eksekusi_h

bool isExecutable(const char * path);
//mengembalikan true bila path menunjuk berkas eksekutabel

void eksekusi(const char * path, char * argv[]);
//I.S. isExecutable(path)
//F.S. terbentuk proses anak yang menjalankan path

#endif
