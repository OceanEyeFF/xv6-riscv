#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[])
{
	int val=0;
	if(argc == 3)
	{
		if(strcmp(argv[1],"-s")==0)
		{
			val=atoi(argv[2]);
			if(val<=0) goto fail;
			sleep(val);
			exit(0);
		}
		/*
		if(strcmp(argv[0],"-ms")==0)
		{
			val=atoi(argv[1]);
			if(val<=0) goto fail;
			usleep(val*1000);
			exit(0);
		}
		*/
		goto fail;
	}

fail:
		printf("usage:\n");
		printf(" sleep -s [second]\n");
//printf(" sleep -ms [milisecond]\n");
		printf(" [value] should be greater than 0\n");
		exit(1);
}
