#include "main.h"

char *_getenv(const char *name)
{
	char **env;

	size_t len = (strlen(name));
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
	}

	return NULL;
}
