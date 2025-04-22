#include "main.h"

int command(char **arg, char *line, int status)
{
	int i = 0;

	if (arg[0] == NULL)
		return (1);

	if (strcmp(arg[0], "exit") == 0)
	{
		free(line);
		exit(status);
	}
	if (strcmp(arg[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1);
	}
	
	return (0);
}
