#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

//#include <sh_memory.h>

#define id 'C'

int main()
{
	int id1;
	key_t key; 
	struct shmid_ds buf;
	if ((key = ftok("./test.txt", id))==-1)
	{
		perror("ftok");
		return 0;
	}
	if ((id1 = shmget(key, 30, 0666 /*IPC_CREAT | IPC_EXCL*/))==-1)
	{
		perror("shmget");
		return 0;
	}

	if (shmctl(id1, IPC_STAT, &buf) == -1)
	{
		perror("shmctl");
		return 0;
	}
	printf("%d \n", buf.shm_segsz);
	shmctl(id1, IPC_RMID, &buf);
	return 0;
}
