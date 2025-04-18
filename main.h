#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define DELIM " \t\r\n\a"

extern char **environ;

void prompt(void);
void parse_line(char *line, char **args);
int command(char **args);
char *find_in_path(char *command);







#endif
