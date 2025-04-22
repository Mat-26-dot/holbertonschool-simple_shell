#include "main.h"

char *find_in_path(char *cmd)
{
	char *path;
	char *path_copy;
	char *token;
	static char full_path[1024];

	if (strchr(cmd, '/'))
		return strdup(cmd);

	path = _getenv("PATH");

	if (!path || path[0] == '\0')
		return (NULL);
	path_copy = strdup(path);

	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");

	while (token)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
