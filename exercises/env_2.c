#include <stdio.h>

extern char **environ;

int main(int argc, char **argv, char **env)
{
	printf("env: %p\n", (void *)env);
	printf("environment: %p\n", (void *)environ);
	return 0;
}
