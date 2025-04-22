#include "main.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t bufsize = 128;
	size_t i = 0;
	int ch;
	char *buf;

	if (!lineptr || !n || !stream)
		return -1;

	if (*lineptr == NULL || *n == 0)
	{
		buf = malloc(bufsize);
		if (!buf)
			return -1;
		*lineptr = buf;
		*n = bufsize;
	}
	else
		buf = *lineptr;

	while ((ch = fgetc(stream)) != EOF)
	{
		if (i + 1 >= *n)
		{
			char *tmp = realloc(buf, *n * 2);
			if (!tmp)
				return -1;
			buf = tmp;
			*lineptr = buf;
			*n *= 2;
		}
		buf[i++] = ch;
		if (ch == '\n')
			break;
	}
	if (i == 0 && ch == EOF)
		return -1;

	buf[i] = '\0';
	return (ssize_t)i;
}

