#include "main.h"

char *find_in_path(char *cmd)
{
	char *path = _getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");
	static char full_path[1024];

	if (strchr(cmd, '/'))
	{
		free(path_copy);
		return cmd;
	}

	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
