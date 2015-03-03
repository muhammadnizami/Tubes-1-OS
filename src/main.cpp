#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "eksekusi.h"
#include "cd.h"

extern "C"{
	#include "mesinkata1.h"
}

#define MAX_ARGC 32

int main(){
	char curDir[1024];
	while (true){
		printDir(getwd(curDir));
		printf("$ ");

		char * argv[MAX_ARGC];
		int argc=0;
		for (STARTKATA("-");!EndKata;ADVKATA()){
			argv[argc] = new char[CKata.Length+1];
			StrFromKata(argv[argc],CKata);
			argc++;
		}
		argv[argc]=NULL;
		printf ("executing");

		for (int i=0;i<argc;i++)
			printf(" %s",argv[i]);
		printf("\n");
		
		if (argc>0){
			if (!strcmp(argv[0],"cd" && argv[1]!=NULL)){
				if (cd(argv[1])==-1)
					printf("cd: %s: No such file or directory\n",argv[1]);
			}
		

	//		if (isExecutable(path))
	//			eksekusi(path,argv);
	//		else
	//			printf("%s: command not found\n",argv[0]);

			//cleanup argv
		}
		for (int j=0;j<argc;j++) delete argv[j];
	}
}
