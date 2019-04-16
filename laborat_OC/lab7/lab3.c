#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <time.h>

int fd_set_blocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
		return -1;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK) ;
}

int main(int argc, char *argv[])
{
	int count; 
	float count1=0;
	int fd1, fd2;
	char buf[BUFSIZ];
	struct stat bufinf;
	float perc=0;
	time_t time_beg;
	time_t time_end;

	if (argc!=3)
	{
		perror("error");
		return 0;
	}

	if ((fd1 = open(argv[1], O_RDONLY))==-1)
	{
		perror("error");
		return 0;
	}

	if ((fd2 = open(argv[2], O_WRONLY | O_CREAT))==-1)
	{
		perror("error");
		return 0;
	}

	if (stat(argv[1], &bufinf)==-1)
	{
		perror("error");
		return 0;
	}

	printf ("it is blocking mode\n");
	time_beg=time(NULL);
	do 
	{
		if ((count = read(fd1, buf, BUFSIZ))==-1)
		{
			perror("error");
			return 0;
		}
		if (write(fd2, buf, count)==-1)
		{
			perror("error");
			return 0;
		}
		count1+=count;
		if (count1/bufinf.st_size >= perc)
		{
			printf("%.0f%%\n", count1/bufinf.st_size*100);
			perc+=0.1;
		}

	} while (count == BUFSIZ);
	time_end=time(NULL);
	printf("100%% \ncopy is completed\nlead time = %ld sec\n", time_end-time_beg);

	if ((close(fd1)==-1) || (close (fd2)==-1))
	{
		perror("error");
		return 0;
	}

	if (((fd1=open(argv[1], O_RDONLY))==-1) || ((fd2=open(argv[2], O_WRONLY | O_CREAT))==-1))
	{
		perror("error");
		return 0;
	}


	if (fd_set_blocking(fd1) == -1)
	{
		perror("error");
		return 0;
	}
	
	perc=0;
	count1=0;
	printf("it is nonblocking mode\n");
	time_beg=time(NULL);
	do 
	{
		count = read(fd1, buf, BUFSIZ);
		if (count > 0)
		{
			if (write(fd2, buf, count)==-1)
			{
				perror("error");
				return 0;
			}
			count1+=count;
		}
		if (count1/bufinf.st_size>=perc)
		{
			printf("%.0f%%\n",count1/bufinf.st_size*100);
			perc+=0.1;
		}
		
	} while (count == BUFSIZ);
	time_end=time(NULL);

	printf("100%% \ncopy is completed\nlead time = %ld sec", time_end-time_beg);

	
	return 0;
}
