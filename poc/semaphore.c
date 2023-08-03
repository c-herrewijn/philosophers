

// sem_open sem_close sem_post, sem_wait, sem_unlink

// flags: -lpthread -lrt

#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int create_semaphore(char *sem_name, size_t value, sem_t **sem)
{
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, value);
	if (*sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			if (sem_unlink(sem_name) < 0)
				return (-1);
			*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, value);
			if (*sem == SEM_FAILED)
				return(-1);
			else
				return(0);
		}
	}
	return(0);
}


int main(void)
{
	sem_t	*sem;
	int 	res;

	res = create_semaphore("fork_stack", 3, &sem);
	printf("res create semaphore: %d\n", res);

	// ----- waiting ...
	res = sem_wait(sem);
	printf("res wait: %d\n", res);
	if (res < 0)
		perror(NULL);
	else
		puts("parent has taken a fork");


	// create child process
	pid_t	new_pid;

	new_pid = fork();
	if (new_pid == 0)
	{
		// run child process
		// ------------------------

		// take fork
		res = sem_wait(sem);
		printf("res wait: %d\n", res);
		if (res < 0)
			perror(NULL);
		else
			puts("child has taken a fork");

		// sleep
		usleep(1000);

		// put fork
		res = sem_post(sem);
		printf("res sem_post: %d\n", res);
		if (res < 0)
			perror(NULL);
		else
			puts("child puts back a fork");
		
		// cleanup
		res = sem_close(sem); // closes the semaphore
		exit(0);
	}

	// run parent process
	// ------------------------
	usleep(400);
	// take fork
	res = sem_wait(sem);
	printf("res wait: %d\n", res);
	if (res < 0)
		perror(NULL);
	else
		puts("parent has taken a fork");
	// take fork
	res = sem_wait(sem);
	printf("res wait: %d\n", res);
	if (res < 0)
		perror(NULL);
	else
		puts("parent has taken a fork");


	// cleanup
	res = sem_close(sem); // closes the semaphore
	printf("res close: %d\n", res);
	if (res < 0)
		perror(NULL);
	res = sem_unlink("fork_stack"); // destroys the semaphore
	printf("res unlink: %d\n", res);
	if (res < 0)
		perror(NULL);
}
