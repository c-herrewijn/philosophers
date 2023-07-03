#include <unistd.h>
#include <pthread.h>
#include <stdio.h>


// note should not be a glob
pthread_mutex_t my_lock;


void *thread_function(void *input)
{
	printf("philosopher nr: %d created\n", *(int *)input);
	pthread_mutex_lock(&my_lock);
	printf("philosopher nr: %d picked up the spoon!\n", *(int *)input);
	sleep(2);
    pthread_mutex_unlock(&my_lock);

	return (NULL);	// where is the return value used?
}

int	main(void)
{
	pthread_t		thread1;
	pthread_t		thread2;

	int				res;
	int				num_1 = 1;
	int				num_2 = 2;

	// create lock (note second argument are optional attributes of the lock)
	res = pthread_mutex_init(&my_lock, NULL);
	printf("res: %d\n", res);

	// create threads
	res = pthread_create(&thread1, NULL, thread_function, (void *)&num_1);
	printf("res: %d\n", res);
	res = pthread_create(&thread2, NULL, thread_function, (void *)&num_2);
	printf("res: %d\n", res);


	// wait for the threads
	pthread_join(thread1, NULL);	// makes the main process wait for the thread;
	pthread_join(thread2, NULL);	// makes the main process wait for the thread;
}
