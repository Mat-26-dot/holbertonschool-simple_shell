#include "main.h"

char *find_in_path(char *cmd)
{
	char *path;
	char *path_copy;
	char *token;
	static char full_path[1024];

	if (strchr(cmd, '/'))		/* Check if command contains a '/' character */
		return strdup(cmd); 	/* If so, treat as a path and return a duplicate */

	path = _getenv("PATH"); 	/* Get the PATH environment variable */

	if (!path || path[0] == '\0') 	/* If PATH is not set or is empty, return NULL */
		return (NULL);
	path_copy = strdup(path); 	/* Duplicate PATH so we can safely tokenize it */

	if (!path_copy) 		/* If strdup fails, return NULL */
		return (NULL);

	token = strtok(path_copy, ":"); /* Tokenize the PATH using ':' as the delimiter */

	while (token)			/* Iterate through each directory in PATH */
	{				/* Set up the full path to the command */
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
		if (access(full_path, X_OK) == 0) /* Check if the constructed path is an executable file */
		{
			free(path_copy); /* Free the duplicated PATH before returning */
			return (strdup(full_path)); /* Return a duplicate of the found full path */
		}
		token = strtok(NULL, ":"); /* Move to the next directory in PATH */
	}

	free(path_copy); 		/* Free the duplicated PATH if command was not found */
	return (NULL);
}
