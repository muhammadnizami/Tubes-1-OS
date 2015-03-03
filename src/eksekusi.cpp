#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

bool isExecutable(const char * path){
//mengembalikan true bila path menunjuk berkas eksekutabel
	return access("/my/file", X_OK) != -1;
}

void eksekusi(const char * path, char * argv[]){
//I.S. isExecutable(path)
//F.S. terbentuk proses anak yang menjalankan path
	pid_t pid;
	int status;
	pid=fork();
	if (pid==0){	
		execvp(path,argv);
	}else {
		assert(pid>0);
		waitpid(pid, &status, WUNTRACED
#ifdef WCONTINUED       /* Not all implementations support this */
        | WCONTINUED
#endif
		);
		fflush(stdout);
	}
}

void eksekusi(const char * path, char * argv[], int in, int out){
//I.S. isExecutable(path)
//F.S. terbentuk proses anak yang menjalankan path
//	dengan stdin dan stdout diredirect ke pid_in dan pid_out
	pid_t pid;
	int status;
	pid=fork();
	if (pid==0){
		//redireksi
		// replace standard input with input file
		if (in>0){
			close(0);
			dup(in);
			close(in);
		}
		// replace standard output with output file
		if (out>1){
			close(1);
			dup(out);
			close(out);
		}

		//override proses
		execvp(path,argv);
	}else {
		assert(pid>0);
		waitpid(pid, &status, WUNTRACED
#ifdef WCONTINUED       /* Not all implementations support this */
        | WCONTINUED
#endif
		);
		if (in>0)close(in);
		if (out>1)close(out);
	}

}
