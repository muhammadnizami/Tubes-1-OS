#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int pass_to_child_pid;

void pass_to_child(int signo)
{
	kill(pass_to_child_pid,SIGINT);
}

bool isExecutable(const char * path){
//mengembalikan true bila path menunjuk berkas eksekutabel
	return access(path, X_OK) != -1;
}

void eksekusi(const char * path, char * argv[]){
//I.S. isExecutable(path)
//F.S. terbentuk proses anak yang menjalankan path
	pid_t pid;
	int status;
	pid=fork();
	if (pid==0){	
		execvp(path,argv);
		
		//bila gagal override
		fprintf(stderr,"%s: command not found\n",path);
		exit(0);
	}else {
		assert(pid>0);

		//signal handler
		pass_to_child_pid=pid;
		signal(SIGINT, pass_to_child);
		signal(SIGTERM, pass_to_child);
		waitpid(pid, &status, WUNTRACED
#ifdef WCONTINUED       /* Not all implementations support this */
        | WCONTINUED
#endif
		);

		//signal handler dikembalikan
		signal(SIGINT,SIG_DFL);
		signal(SIGTERM,SIG_DFL);

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

		//bila gagal override
		fprintf(stderr,"%s: program not found\n",path);
		exit(0);
	}else {
		assert(pid>0);

		//signal handler
		assert(pid>0);
		pass_to_child_pid=pid;
		signal(SIGINT, pass_to_child);
		signal(SIGTERM, pass_to_child);

		waitpid(pid, &status, WUNTRACED
#ifdef WCONTINUED       /* Not all implementations support this */
        | WCONTINUED
#endif
		);

		//signal handler dikembalikan
		signal(SIGINT,SIG_DFL);
		signal(SIGTERM,SIG_DFL);

		if (in>0)close(in);
		if (out>1)close(out);
	}

}
