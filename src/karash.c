#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <sys/wait.h>

#include "parser.h"

#define true 1
#define false 0

#define exit_err(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define exit_suc() exit(EXIT_SUCCESS)

char* read_line(void);
char** parse_line(char* line);
int launch(char** args);

int
main(int argc, char** argv)
{
    char* line;
    char** args;

    printf("Welcome to karash\n");

    while (true) {
	printf("> "); //prompt
	line = read_line();
	args = parse_line(line);
	launch(args);
	// TODO free args
	free(line);
    }

    return 0;
}

/// Readline with simple error handling
char*
read_line(void)
{
    char* line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
	if (feof(stdin)) exit_suc();
	else exit_err("getline failure");
    }

    return line;
}

#define PARSELINE_DELIM " \t\r\n\a"
#define PARSELINE_BUFSIZE 16
char**
parse_line(char* line)
{
    int bufsize = PARSELINE_BUFSIZE;
    int ind = 0;
    char** tokens = malloc(bufsize * sizeof(char*));
    char* pch;

    if (!tokens) exit_err("malloc error");

    pch = strtok(line, PARSELINE_DELIM);
    while (pch != NULL) {
	tokens[ind++] = pch;

	if (ind >= bufsize) {
	    bufsize *= 2;
	    tokens = realloc(tokens, bufsize * sizeof(char*));
	    if (!tokens) exit_err("malloc error");
	}

	pch = strtok(NULL, PARSELINE_DELIM);
    }

    tokens[ind] = NULL;
    return tokens;
}

int
launch(char** args)
{
    pid_t child_pid;
    int child_status;
    int s;
    char** environ;

    s = posix_spawnp(&child_pid, args[0], NULL, NULL, args, environ);
    if (s != 0) exit_err("failed to launch");

    printf("[%d+]\n", child_pid);
    s = waitpid(child_pid, &child_status, 0);
    if (s == -1) exit_err("waipid failed");

    printf("child exit status: %d\n", child_status);
    return 0;
}
