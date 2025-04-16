#include <stdio.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name)
{
	size_t len = (strlen(name));
	for (char **env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
	}

	return NULL;
}

int main(void)
{
	const char *path = "PATH";
	char *value = _getenv(path);
	if (value)
		printf("%s=%s\n", path, value);
	else
		printf("%s not found\n", path);
	return (0);
}


