/*
    This program is analogous to one example from the Udemy course "Introduction to Operating Systems"
*/
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>


#define BUFFER_SIZE 3
#define CYCLES 20

int buffer[BUFFER_SIZE];                                        //shared buffer

int add = 0;  			                                        // place to add next element
int rem = 0;  			                                        // place to remove next element
int num = 0;  			                                        // number elements in buffer

pthread_mutex_t mutexBuffer      = PTHREAD_MUTEX_INITIALIZER;  	// mutex lock for the buffer
pthread_cond_t consumerCondition = PTHREAD_COND_INITIALIZER;    // consumer waits on this cond var
pthread_cond_t producerCondition = PTHREAD_COND_INITIALIZER;    // producer waits on this cond var */

void *producer(void *param) 
{

	for (int i = 1; i <= CYCLES; ++i) 
    {
		
		// Insert into buffer 
		pthread_mutex_lock (&mutexBuffer);	
			
        if (num > BUFFER_SIZE)
        {
			exit(EXIT_FAILURE);  // overflow 
		}

		while (num == BUFFER_SIZE) 
        {  
            // block if buffer is full
			pthread_cond_wait (&producerCondition, &mutexBuffer);
		}
			
		// if executing here, buffer is not full so add element
		buffer[add] = i;
		add = (add+1) % BUFFER_SIZE;
		num++;
		pthread_mutex_unlock (&mutexBuffer);

		pthread_cond_signal (&consumerCondition);
		printf ("producer: inserted %d\n", i);
		fflush (stdout);
	}

	printf("producer quiting\n");
	fflush(stdout);
    
	return NULL;
}

// To consume values. The consumer never terminates
void *consumer(void *param) 
{

	int i;

	while(1) 
    {

        pthread_mutex_lock (&mutexBuffer);
        if (num < 0) 
        {
            exit(EXIT_FAILURE); //underflow
        } 

        while (num == 0) 
        {   // block if buffer is empty
            pthread_cond_wait (&consumerCondition, &mutexBuffer);
        }

        // if executing here, the buffer is not empty so remove an element
        i = buffer[rem];
        rem = (rem+1) % BUFFER_SIZE;
        num--;
        pthread_mutex_unlock (&mutexBuffer);

        pthread_cond_signal (&producerCondition);
        printf ("Consume value %d\n", i);  fflush(stdout);

	}

	return NULL;
}

int main(int argc, char *argv[]) {

	pthread_t producerThread, consumerThread;  

	if(pthread_create(&producerThread, NULL, producer, NULL) != 0) 
    {
		fprintf(stderr, "Error with creating the producer thread\n");
		exit(EXIT_FAILURE);
	}

	if(pthread_create(&consumerThread, NULL, consumer, NULL) != 0)
    {
		fprintf(stderr, "Error with creating the consumer thread\n");
		exit(EXIT_FAILURE);
	}

	pthread_join(producerThread, NULL);
	pthread_join(consumerThread, NULL);

	printf("The main thread quiting\n");

	return 0;
}
