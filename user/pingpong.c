#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

#define MSGSIZE 20

int main(int argc,char* argv[])
{
	if(argc>1)
	{
		printf("Usage: pingpong\n");
		exit(1);
	}
	int p[2];
	int status=1;
	char msgbuf[MSGSIZE];

	int ret=pipe(p);
	if(ret==-1)
	{
		printf("pipe error");
		exit(-1);
	}

	int pid = fork();

	if(pid > 0) // 父亲能够获取子进程的pid
	{
		printf("I'm father\n");
		write(p[1],"ping",MSGSIZE);

		wait(&status);

		read(p[0],msgbuf,MSGSIZE);
		printf("pid: %d , father recieve: %s\n",getpid(),msgbuf);
	}
	else
	{
		sleep(3);
		read(p[0],msgbuf,MSGSIZE);
		printf("I'm child\n");
		printf("pid: %d , child recieve: %s\n",getpid(),msgbuf);
		write(p[1],"pong",MSGSIZE);
	}
	
	exit(0);
}
