#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#include <stdlib.h>

int main()
{
	pid_t pid;
	int pipefd[2];
	if (pipe(pipefd)==-1){
		perror("error");
		exit(0);
	}

	if ((pid=fork())==0)
	{
		printf ("this is child process\n");
		char s1[100];
		if ((read(pipefd[0], s1, 100))==-1)
		{
			perror("error");
			exit(0);
		}
		printf ("%s\n",s1);
	
	
	}
	else 
	{
		printf ("this is parrent process\n");
		char s[]="hello from parent";
		if ((write(pipefd[1], s, 100))==-1)
		{
			perror("error");
			exit(0);
		}
		
	
	}	
	return 0;
}
