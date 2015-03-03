#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

bool isExecutable(const char * path){
//mengembalikan true bila path menunjuk berkas eksekutabel
	return access("/my/file", X_OK) != -1;
}

void eksekusi(const char * path, char * argv[]){
//I.S. isExecutable(path)
//F.S. terbentuk proses anak yang menjalankan path
	pid_t pid;
	pid=fork();
	if (pid==0){	
		execvp(path,argv);
	}else {
		assert(pid>0);
		wait(pid);
	}
}
