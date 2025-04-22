#include "main.h"

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t rd = 0;
	char *args[MAX_ARGS];
	char *cmd_path = NULL;
	pid_t pid;
	int status = 0;
	int interactive = isatty(STDIN_FILENO);
	int wstatus;

	while (1)
	{

		if(interactive)
			prompt();
		rd = _getline(&line, &len);
		if (rd == -1)
		{
			if (interactive)
				putchar('\n');
			break;
		}
		if (line[rd - 1] == '\n')
			line[rd - 1] = '\0';

		parse_line(line, args);

		if (args[0] == NULL)
			continue;
		if (command(args, line, status))
			continue;

		cmd_path = find_in_path(args[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			status = 127;
			continue;
		}
		pid = fork();

		if (pid == 0)
		{
			execve(cmd_path, args, environ);
			perror("execve");
			free(cmd_path);
			free(line);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
			perror("fork");
		else
		{
			waitpid(pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				status = WEXITSTATUS(wstatus);
			free(cmd_path);

		}
	}
	free(line);
	return (status);
}
