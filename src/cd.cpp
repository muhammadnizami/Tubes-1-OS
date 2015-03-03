#include "cd.h"

#include <string.h>
#include <sys/stat.h>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <stdio.h>

bool dirExists(const char * dir){
//mengembalikan true bila ada direktori dir

	struct stat sb;

	if (stat(dir, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
	    return true;
	}else return false;
}

void toParent(char * dir){
	int i = strlen(dir);
	do{
		i--;
	}while (dir[i]!='/');
	dir[i]='\0';
}

char * unitcd(char * from, char * to){
	if(strcmp("..",to)){
		if (strcmp(".",to)){
			int a = strlen(from);
			from[a]='/';
			strcpy(from+a+1,to);
			if (dirExists(from))
				return from;
			else{
				from[a]='\0';
				return NULL;
			}
		}
	}else{
		toParent(from);
	}
}

char * recursivecd(char * from, char * to){
	if (to[0]=='\0') return from; //basis
	char next[256];
	int i=0;
	while (to[i]!='/' && to[i]!='\0'){
		next[i]=to[i];
		i++;
	}
	next[i]='\0';
	if (unitcd(from,next))
		return recursivecd(from,to+i+1);
	else
		return NULL;
}

char * cd(char * from, char * to){
//I.S. dirExists(from)
//F.S. from berpindah ke to bila direktori tersebut ada
	int a;
	switch(to[0]){
	case '/':
		if(dirExists(to)){
			strcpy(from, to);
			return from;
		}else
			return NULL;
	case '~':
		char tmp[1024];
		getHomeDir(tmp);
		a = strlen(tmp);
		strcpy(tmp+a,to+1);
		if (dirExists(tmp)){
			strcpy(from,tmp);
			return from;
		}else{
			return NULL;
		}
	default:
		return recursivecd(from,to);
/*		a = strlen(from);
		from[a]='/';
		strcpy(from+a+1,to);
		if (dirExists(from))
			return from;
		else{
			from[a]='\0';
			return NULL;
		}*/
	}
}

char * getHomeDir(char * dst){
	if (dst != NULL){
		struct passwd *pw = getpwuid(getuid());
		strcpy(dst, pw->pw_dir);
		return dst;
	}else {
		static char tmp[1024];
		return getHomeDir(tmp);
	}
}

void printDir(char * dir){
	char* homeDir = getHomeDir(NULL);
	int a = strlen(homeDir);
	if (!strncmp(homeDir,dir,a)){
		printf("~");
		printf("%s",dir+a);
	}else{
		printf("%s",dir);
	}
}

