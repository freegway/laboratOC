#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	time_t time_begin=time(NULL), time_end;
	int fd1, fd2,count;
        char buf[BUFSIZ];
        if (argc!=3){
                perror("error");
		exit(0);
	}
        if ((fd1=open(argv[1],O_RDONLY,0))==-1){
                perror("error");
		exit(0);
	}
        if ((fd2=creat(argv[2],0666))==-1){
                perror("error");
		exit(0);
	}
        do
        {
                count=read(fd1,buf,BUFSIZ);
                if (write(fd2,buf,count)==-1){
                        perror("error");
			exit(0);
		}
        }
        while(count==BUFSIZ);
	time_end=time(NULL);
	printf ("time is %d\n",time_end-time_begin);
}

