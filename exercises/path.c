#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 65

void prompt(void)
{
	printf("shell$ ");
	fflush(stdout);
}

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	char *args[MAX_ARGS];
	ssize_t rd;

	while (1)
	{
		prompt();

		rd = getline(&line, &len, stdin);
		if (rd == -1)
		{
			perror("getline");
			break;
		}

		line[strcspn(line, "\n")] = 0;

		if (line[0] == '\0') 
			continue;

		int i = 0;

		char *token = strtok(line, " ");
		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i++] = token;
			token = strtok(NULL, " ");

		}

		args[i] = NULL;

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		else if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
				perror("execvp");

			exit(EXIT_FAILURE);
		}
		else
		{
			int status;
			waitpid(pid, &status, 0);
		}
	}

	free(line);
	return 0;
}
