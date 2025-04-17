#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Access to the environment variables
extern char **environ;

/**
 * _unsetenv - Removes an environment variable.
 * @name: The name of the variable to remove.
 * Return: 0 on success, -1 on error.
 */
int _unsetenv(const char *name) 
{
    // Validate input: name must not be NULL or contain '='
    if (!name || strchr(name, '=')) return -1;

    size_t len = strlen(name);

    // Loop through environment variables
    for (int i = 0; environ[i]; i++) {
        // If the variable matches "name="
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=') {
            // Shift all remaining variables left by one to remove the match
            for (; environ[i]; i++) {
                environ[i] = environ[i + 1];  // Includes moving the NULL terminator
            }
            return 0; // Variable removed
        }
    }

    // Variable not found, but no error

}

int main(void) 
{
    // Print the value of MYVAR before unsetting
    printf("Before unset: %s\n", getenv("MYVAR"));

    // Attempt to remove MYVAR from the environment
    _unsetenv("MYVAR");

    // Print the value after unsetting (should be NULL or (null))
    printf("After unset: %s\n", getenv("MYVAR"));

    return 0;
}

