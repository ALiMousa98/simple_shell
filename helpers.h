#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>

#define RET 0
#define BUILTIN_SET 2
#define BUILTIN_EXPORT 3
#define BUILTIN_HIST 4
#define EXIT  5
#define ASSIGN_LOCALVAR 1
#define END_OF_FILE 6
#define PRINT_ENV 7


extern void print_enviro(char **env);
extern void end_file(char *myline);

#endif
