#include "main.h"

int command(char **arg)
{
	int i = 0;

	if (arg[0] == NULL)
		return (1);

	if (strcmp(arg[0], "exit") == 0)
		exit(0);

	if (strcmp(arg[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1);
	}
	
	return (0);
}
