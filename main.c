#include "main.h"

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t rd = 0;
	char *args[MAX_ARGS];
	char *cmd_path = "";
	pid_t pid;
	int status;

	while (1)
	{
		prompt();
		rd = getline(&line, &len, stdin);
		if (rd == -1)
		{
			if (feof(stdin))
				break;
			perror("getline");
			continue;
		}

		parse_line(line, args);

		if (args[0] == NULL)
			continue;
		if (command(args))
			continue;

		cmd_path = find_in_path(args[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
			continue;
		}
		pid = fork();

		if (pid == 0)
		{
			execve(cmd_path, args, environ);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
			perror("fork");
		else
			waitpid(pid, &status, 0);
	}
	free(line);
	return (0);
}
