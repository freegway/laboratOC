#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

#define id ' C '

int main(int argc, char *argv[])
{
	key_t key;
	size_t size=30;


	if (argc!=2)
	{
		printf("few arguments\n");
		return 0;
	}
	
	if ((key = ftok(argv[1], id))==-1)
	{
		perror("error");
		return 0;
	}
	
	if (shmget(key, size, IPC_CREAT | IPC_EXCL)==-1)
	{
		perror("error");
		return 0;
	}	

	

	
}
