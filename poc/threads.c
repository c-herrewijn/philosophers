// gcc -lpthread poc/threads.c

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void *f_thread(void *input)
{
	int number;

	number = *(int *)input;
	printf("thread speaking, received number: %d\n", number);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	int			res;
	int			number1;
	int			number2;

	number1 = 42;
	number2 = 242;

	/*
	pthread_create()
	arg[1]: thread address
	arg[2]: optionally, attributes can be specified via an pthread_attr_t object // NOT used for philosophers!
	arg[3]: start function executed by the tread (should have void* as input and output)
	arg[4]: optionally: argument for start function of type void* 
	*/
    res = pthread_create(&thread1, NULL, f_thread, (void *) &number1);
	printf("res: %d\n", res);
	pthread_join(thread1, NULL);	// makes the main process wait for the thread;
    
	res = pthread_create(&thread2, NULL, f_thread, (void *) &number2);
	printf("res: %d\n", res);
	pthread_join(thread2, NULL);	// makes the main process wait for the thread;

	// sleep(1);
	return (0);
}

