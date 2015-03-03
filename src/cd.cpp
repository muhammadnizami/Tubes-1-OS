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

int cd(char * to){
//I.S. ada working directory
//F.S. working directory berpindah ke to bila direktori tersebut ada
//	mengembalikan 0 bila berhasil
//	bila tidak, working directory tetap, return -1
	if(to[0]=='~'){
		char * path;
		path = new char[1024];
		getHomeDir(path);
		strcat(path,to+1);
		int retval= chdir(path);
		delete(path);
		return retval;
	}else	return chdir(to);
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

