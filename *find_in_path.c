#include "main.h"

char *find_in_path(char *cmd)
{
	char *path = getenv("PATH");
	char *token = strtok(strdup(path), ":");
	static char full_path[1024];

	if (strchr(cmd, '/'))
		return cmd;

	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s%s", token, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		token = strtok(NULL, ":");
	}

	return (NULL);
}
