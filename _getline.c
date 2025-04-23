#include "main.h"

ssize_t _getline(char **lineptr, size_t *n)
{
	size_t bufsize = 1024;	/* Start with a buffer size of 1024 */
	ssize_t i = 0;		/* Keeps track of how many chars we've read */
	char c = '\0';		/* This will hold each char we read */
	char *buffer;

	if (*lineptr == NULL || *n == 0)	/* If the buffer doesn't exist yet, allocate it */
	{
		*lineptr = malloc(bufsize);
		if (!*lineptr)
			return -1;	/* Return -1 if malloc fails */
		*n = bufsize;
	}

	buffer = *lineptr;

	while (1)
	{
		ssize_t r = read(STDIN_FILENO, &c, 1);	/* Read one character from stdin */
		if (r == -1 || (r == 0 && i == 0))	/* If read fails, or nothing to read and nothing read yet, return -1 */
			return -1;
		if (r == 0)			/* If we hit end-of-file after reading somrthing, break out of loop */
			break;
		if (i >= (ssize_t)(*n - 1))	/* If buffer is full, make it bigger */
		{
			bufsize *= 2;		/* Double the buffer size */
			buffer = realloc(buffer, bufsize);
			if (!buffer)
				return -1; 	/* realloc failed */
			*lineptr = buffer;
			*n = bufsize;
		}
		buffer[i++] = c;	/* Add the character to the buffer */
		if (c == '\n')		/* If we hit a newline, stop reading */
			break;
	}
	buffer[i] = '\0';	/* Null-terminate the string */	
        }
	return i;	/* Return how many characters we read */
}

