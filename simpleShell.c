#include "helpers.h"

/**
 * print_prompt - prints a prompt
 * Return: void
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
 * get_line - get line
 * @line: input line
 * Return: result line
 */
char *get_line(char *line)
{
	fgets(line, 100, stdin);
	line[strcspn(line, "\n")] = 0;
	return (line);
}

/**
 * parser - parsing input to choices
 * @_cmd: first command ketword
 * @cmd: entire command line
 * @params: parameters
 * Return: choice
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
	if (strcmp(_cmd, "^D") == 0)
		return (END_OF_FILE);
	if (strcmp(_cmd, "env") == 0)
		return (PRINT_ENV);
	strcpy(cmd, temp[0]);
	for (j = 0; j < i; j++)
		params[j] = temp[j];
	params[i] = NULL;
	return (RET);
}

/**
 * main - main function
 * Return: int
 */

int main(void)
{
	int status, ch, ret_pid;
	char myline[100], cmd[50], check_command[100];
	char *params[50] = {NULL}, **env = NULL;

	while (1)
	{
		print_prompt();
		get_line(myline);
		if (strcmp(myline, "\0") == 0)
			continue;
		ch = parser(myline, cmd, params);
		if (ch == -EXIT)
			exit(0);
		if (ch == END_OF_FILE)
		{
			end_file(myline);
			break;
		}
		if (ch == PRINT_ENV)
			print_enviro(env);
		if (ch == RET)
		{
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
	} return (RET);
}

