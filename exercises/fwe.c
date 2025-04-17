#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t my_pid;
	int i = 0;
	int status = 0;

	for (i = 0; i < 5; i++)
	{
		my_pid = fork();

		if (my_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (my_pid == 0) //CHILD
		{
			printf("Child %d executing ls -l /tmp: \n", i + 1);
			execlp("ls", "ls", "-l", "/tmp", (char *)NULL);
			perror("execlp");
			exit(EXIT_FAILURE);
		}
		else //PARENT
		{
			waitpid(my_pid, &status, 0);
			if(WIFEXITED(status))
				printf("Child %d exited with status %d\n", i + 1, WEXITSTATUS(status));
			else
				printf("Child %d is broken\n", i + 1);
		}
	
	}

	return (0);
}
