#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum Mode 
{
	Privileged = 1,
	Unprivileged = 0
};

enum Mode mode;

int evaluate_statement(char *statement)
{
	char *p;
	if (!strcmp(statement, "ls"))
	{
		system("ls");
		return 0;
	}
	else if (!strcmp(statement, "pwd"))
	{
		system("pwd");
		return 0;
	}
	else if((p = strstr(statement, "cat")) != NULL && mode == Privileged)
	{
		char *filename = p + 4;
		printf("%s\n", filename);
		char *full_command = malloc(60);
		snprintf(full_command, 60, "cat %s", filename);
		return system(full_command);

		free(full_command);
	}
	printf("Invalid command '%s', or attempt to execute a privileged command '%s' without permission.\n", statement, statement);
	return 1;
}

int main(int argc, char *argv[])
{
	char eval_buff[50];
	char mode_buff[10];

	// Print intro and begin event loop
	printf("PACKShell v0.0.0.1.2.5l6.3\n");

	// read user args and set the mode
	if (argc < 2)
	{
		printf("Usage: packshell <MODE> (1 for interactive, 0 for single-mode");
		exit(1);
	}
	int user_provided_mode = atoi(argv[1]);
	switch(user_provided_mode) 
	{
		case 1:
			mode = Privileged;
			break;
		case 0:
			mode = Unprivileged;	
			break;
		default:
			printf("Usage: packshell <MODE> (1 for privileged, 0 for unprivileged");
			break;
	}

	int err = 0;
	while (err == 0)
	{
		printf("$ ");
		scanf("%50[^\n]", eval_buff);
		err = evaluate_statement(eval_buff);
		fflush(stdin);
		memset(eval_buff, 0, 50);
	}
}
