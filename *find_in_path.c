#include "main.h"

char *find_in_path(char *cmd)
{
	char *path = _getenv("PATH");
	char *path_copy;
	char *token;
	static char full_path[1024];

	if (strchr(cmd, '/'))
		return cmd;

	if (!path || path[0] == '\0')
		return (NULL);
	path_copy = strdup(path);
	token = strtok(path_copy, ":");

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
