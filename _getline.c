#include "main.h"

ssize_t _getline(char **lineptr, size_t *n)
{
	size_t bufsize = 1024;
	ssize_t i = 0;
	char c = '\0';
	char *buffer;

	if (*lineptr == NULL || *n == 0)
	{
		*lineptr = malloc(bufsize);
		if (!*lineptr)
			return -1;
		*n = bufsize;
	}

	buffer = *lineptr;

	while (1)
	{
		ssize_t r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && i == 0))
			return -1;
		if (r == 0)
			break;
		if (i >= (ssize_t)(*n - 1))
		{
			bufsize *= 2;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
				return -1;
			*lineptr = buffer;
			*n = bufsize;
		}
		buffer[i++] = c;
		if (c == '\n')
			break;
	}
	buffer[i] = '\0';
	return i;
}

