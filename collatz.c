/** @file main.c
 *  @brief Starting point of the program
 *
 *  Parses arguments and places it into a struct
 *  then prints the struct
 *
 *  @author Raymond Fleming
 *  @bug No known bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define arraySize 550

void initializeArray();
int computeTime();
void printArray();
void createThreads(int n, int threadcount, pthread_t threads[]);
void *threadCompute(void *);
void joinThreads(int threadCount,pthread_t threads[]);
int storageArray[arraySize],current=1;


int main(int argc, char** argv){
    int n=0,threadCount=0;
    int count=0,time=0,exitStatus=0;
    
    
    initializeArray();

    if (argc==3)
    {
       int threadCount = atoi(argv[1]);
       printf("\n\nthreadcount is %d\n",threadCount); 
       pthread_t threads[threadCount];
       n= atoi(argv[2]);
       printf("\n\nstarting thread creation\n");
       createThreads(n,threadCount,threads);
       joinThreads(threadCount,threads);
       printArray();
	}
    else
       printf("\n\ninvalid arguments supplied, exiting\n");
    return exitStatus;
}

void initializeArray()
{
    int i=0;
    for (i=0;i<arraySize;i++)
        storageArray[i]=0;
}

int computeTime(int i)
{
    int time=0;
    do{
       if (i%2==0)
           i=i/2;
       else
           i=3*i+1;
       time++;
    }while (i!=1);
    return time;
}

void printArray()
{
    int i=0;
    int total=0;
    printf("\n\n-------------------------------------------\n");
    for (i=0;i<arraySize;i++)
    {
        printf("\nfrequency of %d is %d",i,storageArray[i]);
        total+=storageArray[i];
    }
    printf("\n\nTotal number is %d\n\n",total);
    
}

void *threadCompute(void *nptr)
{
	int i=0,time=0;
	int n=*((int *) nptr);
	i=current;
	current++;
//	printf("\n\nn is %d\n",n);
	while (i<=n)
	{
	//	printf("\n\ncurrent is %d\n",i);
		time=computeTime(i);
		storageArray[time]++;
		i=current;
		current++;
	}
	return NULL;
}

void createThreads(int n, int threadCount, pthread_t threads[])
{
	int i=0, num=n;
//	printf("\n\ncreating thread\n");
	for (i=0;i<threadCount;i++)
	{
//	   printf("\n\ncreating thread %d\n",i);
	   pthread_create(&threads[i],NULL,threadCompute,(void *)&num);
//	   printf("\n\nthreads created\n");
	}
}

void joinThreads(int threadCount,pthread_t threads[])
{
    int i=0;
    for (i=0;i<threadCount;i++)
    {
        pthread_join(threads[0],NULL);
    }
}
