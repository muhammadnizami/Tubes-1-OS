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

char * homeDirToCurlyDash(char * dir, char * buf){
//I.S. dir berisi path
//F.S. dir disalin ke buf
//	apabila bagian depan dir merupakan home directory,
//	home directory disalin dengan ~
	if (buf!=NULL){
		char* homeDir = getHomeDir(NULL);
		int a = strlen(homeDir);
		if (!strncmp(homeDir,dir,a)){
			sprintf(buf,"~");
			strcat(buf,dir+a);
		}else{
			strcpy(buf,dir);
		}
	}else	{
		static char tmp[1024];
		return homeDirToCurlyDash(dir,tmp);
	}
}

char * curlyDashToHomeDir(char * dir, char * buf){
//I.S. dir berisi suatu path
//F.S. jika buf == NULL, suatu variabel buffer yang statik akan berisi
//		path yang ~ diganti dengan home directory, dan return
//	jika buf != NULL, buf berisi dir yang ~ diganti home directory
//		return buf
	if (buf!=NULL){
		if(dir[0]=='~'){
			getHomeDir(buf);
			strcat(buf,dir+1);
			return buf;
		}else{
			strcpy(buf,dir);
			return buf;
		}
	}else{
		static char tmp[1024];
		return curlyDashToHomeDir(dir,tmp);
	}
}
