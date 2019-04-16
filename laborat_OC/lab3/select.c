#include <sys/select.h>
#include <sys/time.h>

#include <sys/wait.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>

#include <unistd.h>

#include <stdlib.h>

#include <time.h>

#define MAX(a, b) (a > b ? a : b)

int rdwr(int fd_r, int fd_w)
{
	char buf[BUFSIZ];
	int count1, count2;
	
	fd_set fd_in,fd_out;

	FD_ZERO(&fd_in);
        FD_ZERO(&fd_out);

        FD_SET(fd_r,&fd_out);
        FD_SET(fd_w,&fd_in);


	int ret;

        do {
        ret=select ( MAX(fd_r ,fd_w)+1, &fd_in, &fd_out, NULL, NULL);

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

}	

int main(int argc, char *argv[])
{
	char buf[BUFSIZ];
	size_t count;
	int fd_r, fd_w1, fd_w2;
 	time_t t1, t2;	
	pid_t pid;

	if (argc != 4)
	{
		printf ("usage: incorrect arguments\n1)copy file\n2)file for write in parent process\n3)file for write in child process\n");
		return 0;
	}
	if ((fd_r = open(argv[1], O_RDONLY, 0)) == -1)
	{
		perror("error open fd_read");
		return 0;
	}
	if ((fd_w1 = open(argv[2], 0666 | O_CREAT)) == -1)
	{
		perror("error open fd_write1");
		return 0;
	}
	if ((fd_w2 = open(argv[3], 0666 | O_CREAT)) == -1)
	{
		perror("error open fd_write2");
		return 0;
	}

	if ((pid = fork()) == -1)
	{
		perror("fork");
		return 0;
	}else if (pid == 0)
	{
		printf ("this is child process\n");
		t1 = time(0);
		if (rdwr(fd_r, fd_w2) == -1)
			return 0;
		printf ("child process: copy completed, time is %d\n", time(0)-t1);
	}else 
	{
		printf ("this is parent process\n");
		wait(0);
		if (lseek(fd_r, 0, SEEK_SET) == -1)
		{
			perror("lseek");
			return 0;
		}
		t2=time(0);
		if (rdwr(fd_r, fd_w1) == -1)
			return 0;
		printf ("parent process:copy completed, time is %d\n", time(0)-t2);

	}
	return 0;
}
