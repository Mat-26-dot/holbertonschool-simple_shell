#include <stdio.h>
#include <unistd.h>

/**
 * main - fork examplehfsdjhsdjkf
 * 
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid = getpid();
    pid_t child_pid;
    int i = 0;

    for (i = 0; i < 5; i++)
{
	child_pid = fork();
    	if (child_pid == -1)
    	{
        	perror("Error:");
        	return (1);
    	}
    	if (child_pid == 0)
    	{
	
		printf("(%u) Nooooooooo!\n", my_pid);
		break;
    	}
    	else
    	{
        	printf("(%u) %u, I am your father\n", my_pid, child_pid);
    	}
   	}
    return (0);
}
