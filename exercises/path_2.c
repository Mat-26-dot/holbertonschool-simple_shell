#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void print_path_dirs(void)
{
	char *path = _getenv("PATH");
	if (!path)
		return;

	char *copy = strdup(path);
	char *token = strtok(copy, ":");
	while (token)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}

	free(copy);
}

int main(void)
{
	print_path_dirs();
	return (0);
}
