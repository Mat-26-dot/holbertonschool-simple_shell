#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _setenv - Adds or modifies an environment variable.
 * @name: The name of the variable.
 * @value: The value to set.
 * @overwrite: If non-zero, replaces the variable if it exists.
 * Return: 0 on success, -1 on error.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    // Validate inputs
    if (!name || !value || strchr(name, '=')) return -1;

    size_t len = strlen(name);
    size_t new_len = len + strlen(value) + 2; // +1 for '=' and +1 for '\0'

    // Build the "NAME=VALUE" string
    char *new_var = malloc(new_len);
    if (!new_var) return -1;
    snprintf(new_var, new_len, "%s=%s", name, value);

    // Check if the variable already exists
    for (int i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
        {
            if (!overwrite)
            {
                free(new_var); // Don't overwrite, free new value
                return 0;
            }

            // Overwrite existing entry
            free(environ[i]);
            environ[i] = new_var;
            return 0;
        }
    }

    // Count current environment variables
    int count;
    for (count = 0; environ[count]; count++);

    // Allocate new environment array (1 extra for new var + 1 for NULL)
    char **new_environ = malloc(sizeof(char *) * (count + 2));
    if (!new_environ)
    {
        free(new_var);
        return -1;
    }

    // Copy old environ pointers into new array
    for (int i = 0; i < count; i++)
        new_environ[i] = environ[i];

    // Add new variable and NULL-terminate
    new_environ[count] = new_var;
    new_environ[count + 1] = NULL;

    // Point environ to the new array
    environ = new_environ;

    return 0;
}

int main(void)
{
    // Set a custom environment variable
    if (_setenv("MYVAR", "Custom Value", 1) == -1)
    {
        perror("_setenv");
        return 1;
    }

    // Retrieve and print it using getenv
    printf("MYVAR=%s\n", getenv("MYVAR"));
    return 0;
}

