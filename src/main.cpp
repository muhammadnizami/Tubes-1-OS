#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

//untuk redirect
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "eksekusi.h"
#include "cd.h"

extern "C"{
	#include "mesinkata1.h"
}

#define MAX_ARGC 32

void executeOneCommand(int pipeinfd);

int main(){
	while (true){
		char curDir[1024];
		printDir(getwd(curDir));
		printf("$ ");
		executeOneCommand(0);
	}
}

void executeOneCommand(int pipeinfd){
	int pipingres = -1;
	int pipesfd[2];

	int in=pipeinfd;
	int out=1;

	char * argv[MAX_ARGC];
	int argc=0;
	if (status==stat_opr) ADVKATA();//dummy sementara.
					//operator redirect dan pipeline belum dikerjakan
	for (STARTKATA("-");!EndKata;ADVKATA()){
		if ( status == stat_arg ){
			argv[argc] = new char[CKata.Length+1];
			StrFromKata(argv[argc],CKata);
			argc++;
		} else{
			char buf[1024];
			StrFromKata(buf,CKata);
			if (!strcmp(buf,"<")){
				ADVKATA();
				if (EndKata){
					printf("syntax error near unexpected token `newline'\n");
					break;
				}
				StrFromKata(buf,CKata);
				in = open(buf, O_RDONLY);

				printf("in: %d\n",in);
			}else if (!strcmp(buf,">")){
				ADVKATA();
				if (EndKata){
					printf("syntax error near unexpected token `newline'\n");
					break;
				}
				StrFromKata(buf,CKata);
				out = open(buf, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

				printf("out: %d\n",out);
			}else if (!strcmp(buf,"|")){
				ADVKATA();
				pipingres = pipe(pipesfd);
				if (pipingres==-1)
					printf("pipe failed\n");
				else
					out = pipesfd[1];
				break;
			}else break;
		}
	}
	argv[argc]=NULL;
	printf ("executing");

	for (int i=0;i<argc;i++)
		printf(" %s",argv[i]);
	printf("\n");

	if (argc>0){
		if (!strcmp(argv[0],"cd") && argv[1]!=NULL){
			if (cd(argv[1])==-1)
				printf("cd: %s: No such file or directory\n",argv[1]);
		}else	eksekusi(argv[0],argv,in,out);
		//cleanup argv
		for (int j=0;j<argc;j++) delete argv[j];
		if (pipingres!=-1)executeOneCommand(pipesfd[0]);
	}
}
