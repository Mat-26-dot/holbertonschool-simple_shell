#include "main.h"

char *_getenv(const char *name)
{
	int i = 0;
	size_t len = strlen(name);

	for (i = 0; environ[i]; i++)	/* Loop through the environment variables */
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')	/* See if the start of this env variable matches 'name' */
											/* strncmp just checks the first few letters (length of 'name') */
		 		return (environ[i] + len + 1);				/* Also check if the next char is '=' so we only get exact matches */
	}		/* Got a match, so just return where the value starts */
	return (NULL);
	/* Didn't find variable, so return NULL */
}
