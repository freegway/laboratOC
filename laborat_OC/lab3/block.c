#include <sys/time.h>

#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>

#include <unistd.h>

#include <stdlib.h>

#include <time.h>
#include <sys/wait.h>

int rdwr(int fd_r, int fd_w)
{
	char buf[BUFSIZ];
	int count;
		do
                {
                        if ((count = read(fd_r, buf, BUFSIZ)) == -1)
                        {
                                perror("read");
                                return -1;
                        }
                        if (write(fd_w, buf, count) == -1)
                        {
                                perror("write fd_w");
                                return -1;
                        }
                } while (count == BUFSIZ);
		return 0;

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
