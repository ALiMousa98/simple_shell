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



/*char line[100];
char cmd[50];
char *params[50] = {NULL};
*/

/**
 *
 *
 */

void print_prompt(void)
{
	struct utsname buf;
	char buf2[200];

	uname(&buf);
	getcwd(buf2, 200);
	printf("%s@%s:%s$ ", getenv("USER"), buf.nodename, buf2);
}

/**
 *
 *
 *
 */
char *get_line(char *line)
{
	
	fgets(line, 100, stdin);
	line[strcspn(line, "\n")] = 0;
	return (line);
}

/**
 *
 *
 */


int parser(char *_cmd, char *cmd, char **params)
{
	char *temp[50];
	int i = 0;
	int j;
	char *token = strtok(_cmd, " ");

	while (token != NULL)
	{
		temp[i++] = token;
		token = strtok(NULL, " ");
	}
	if (strcmp(_cmd, "exit") == 0)
		return (-EXIT);
	strcpy(cmd, temp[0]);
	for (j = 0; j < i; j++)
		params[j] = temp[j];
	params[i] = NULL;
	return (RET);
}

/**
 *
 *
 */

int main(void)
{
	int status;
	char myline[100];
	int ch;
	char cmd[50];
	char *params[50] = {NULL};
	
	while (1)
	{
		print_prompt();
		get_line(myline);
		/* strcpy(myline, line);*/
		if (strcmp(myline, "\0") == 0)
			continue;
		ch = parser(myline, cmd, params);
		if (ch == -EXIT)
			exit(0);
		if (ch == RET)
		{
			char check_command[100];
			int ret_pid;

			sprintf(check_command, "which %s >/dev/null 2>&1", params[0]);
			if (system(check_command) == 0)
			{
				ret_pid = fork();
				if (ret_pid < 0)
					printf("Fork Faild \n");
				else if (ret_pid > 0)
					wait(&status);
				else
				{
					execvp(cmd, params);
					printf("%s Command Not Found\n", params[0]);
				}
			}
			else
				printf("%s Command Not Found\n", params[0]);
		}
	} /* While(1)*/
	return (RET);
}

