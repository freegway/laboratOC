#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
	pid_t pid;
	switch(pid=fork())
	{
		case -1:
			perror("error\n");
			exit(0);
		break;
		case 0:
			printf("this is child process.\nMy pid=%d.\nPid my parent=%d.\n",getpid(), getppid());
			printf("after 5 second the child process is complete\n");
		       sleep(5);
	       	       exit(0);
		break;
		default:
			printf("This is parent process.\nMy pid=%d.\nPid my child process=%d.\n",getpid(), pid);
			printf("Waiting for the end of the child process\n");
			wait(0);
			printf("Completing the parent process\n");
		break;		
	}
	return 0;
}
