#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pipefd[2];
	int size=25;
	pid_t pid;
	time_t t;
	char *curtime;
	if (pipe(pipefd)==-1)
	{
		perror("error");
		return 0;
	}

	if (!(pid=fork()))
	{
		int i;
		for (i=0; i<10; i++)
		{
			t=time(NULL)+i;
			curtime=ctime(&t);
			write(pipefd[1], curtime, strlen(curtime)); 
		}
		size=strlen(curtime);
		exit(EXIT_SUCCESS);
	}
	else 
	{
		char buftime[26];
		int i;
		wait(0);
		for (i=0; i<10; i++)
		{
			read(pipefd[0], buftime, size);
			printf ("%s", buftime);
			sleep(1);
		}
		exit(EXIT_SUCCESS);

	}

	return 0;
}
