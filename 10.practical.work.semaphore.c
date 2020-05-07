#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock;

void* pP(void* args)
{
	pthread_detach(pthread_self());
	for (int i=2; i < 100000; i++)
	{
		for (int j=i-1; j>0; j--)
		{
			if (j==1)
			{
				pthread_mutex_lock(&lock);
				printf("prime: %d\n", i);
				pthread_mutex_unlock(&lock);
			} else if (i%j==0)
			{
				break;
			}
		}
	}
	pthread_exit(NULL);
}

void* pFibonacci(void* args)
{
	pthread_detach(pthread_self());
	int c1 = 0; c2 = 1; c3 = c1 + c2;
	int check = 0;
	while (check==0)
	{
		pthread_mutex_lock(&lock);
		printf("Fibonacci: %d\n", cur3);
		pthread_mutex_unlock(&lock);
		c1 = c2; c2 = c3; c3 = c1 + c2;
		if (c3 > 100000)
		{
			check = 1;
		}
	}
	pthread_exit(NULL);
}
int main()
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1,NULL,pP,NULL);
	pthread_create(&t2,NULL,pFibonacci,NULL);

	printf("Created new threads (%lu) & (%lu)\n",t1,t2);

	pthread_exit(NULL);
	pthread_mutex_destroy(&lock);
        return 0;
}
