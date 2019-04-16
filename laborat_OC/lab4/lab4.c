#include <stdio.h>

#include <pthread.h>

#include <unistd.h>

void* threadFunc1(void* arg)
{
	int i;
	for (i=0; i<=5; i++)
		printf ("this is pthread1\n");
}

void* threadFunc2(void* arg)
{
	int i;
	for (i=0; i<=5; i++)
		printf ("this is pthread2\n");
}

int main()
{
	pthread_t tid1, tid2;
	const pthread_attr_t* attr=NULL;
	void* arg=NULL;
	pthread_create(&tid1, NULL, threadFunc1, arg);
	pthread_create(&tid2, NULL, threadFunc2, arg);
	printf ("%d\n",pthread_cancel(tid2));
	printf("main\n");
	pthread_join(tid2, NULL);
	return 0;
}
