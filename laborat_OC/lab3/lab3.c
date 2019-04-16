#include <sys/select.h>
#include <sys/time.h>

#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>

#include <unistd.h>

#include <stdlib.h>

#include <time.h>

#define MAX(A ,B) ( (A) > (B) ? (A) : (B) )

int main(int argc, char *argv[])
{
	time_t time_begin=time(NULL), time_end;
	
	fd_set fd_in,fd_out;
	struct timeval tv;
	
	char buf[BUFSIZ];
	size_t count1=0, count2=0;

	int fd_r,fd_w;

	if (argc!=3)
	{
		printf("Error argc=%d\n",argc);
		exit(0);
	}
	if ((fd_r=open(argv[1],O_RDONLY, 0))==-1)
	{
		perror("error open_r");
		exit(0);
	}
	if ((fd_w=creat(argv[2],0666))==-1)
	{
		perror("error open_w");
		exit(0);
	}
	

	FD_ZERO(&fd_in);
	FD_ZERO(&fd_out);

	FD_SET(fd_r,&fd_out);
	FD_SET(fd_w,&fd_in);

	tv.tv_sec=10;
	tv.tv_usec=0;

	int ret;

	do {
	ret=select ( MAX(fd_r ,fd_w)+1, &fd_in, &fd_out, NULL, &tv);

	if (ret == -1)
		perror("error select");
	else if (ret == 0);

	else 
	 {
		if (FD_ISSET (fd_r, &fd_out))
		{
			if ( (count1=read(fd_r, buf, BUFSIZ)) == -1)
			{
				perror("error read");
				exit(0);
			}	
		}
		
		if (FD_ISSET (fd_w, &fd_in))
		{
			if ( (count2=write(fd_w, buf, count1)) == -1)
			{
				perror("error write");
				exit(0);
			}
		}	
	}
	}
	while(count1==BUFSIZ);
		
	time_end=time(NULL);
	printf("time is=%d\n",time_end-time_begin);

	return 0;
}

