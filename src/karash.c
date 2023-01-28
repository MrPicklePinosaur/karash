#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

char* read_line(void);
char** parse_line(char* line);

int
main(int argc, char** argv)
{
    char* line;

    printf("Welcome to karash\n");

    while (true) {
	printf("> "); //prompt
	line = read_line();
	parse_line(line);
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
	if (feof(stdin)) {
	    exit(EXIT_SUCCESS);
	} else {
	    perror("getline failure");
	    exit(EXIT_FAILURE);
	}
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

    if (!tokens) {
	perror("malloc error");
	exit(EXIT_FAILURE);
    }

    pch = strtok(line, PARSELINE_DELIM);
    while (pch != NULL) {
	tokens[ind++] = pch;

	if (ind >= bufsize) {
	    bufsize *= 2;
	    tokens = realloc(tokens, bufsize * sizeof(char*));
	    if (!tokens) {
		perror("malloc error");
		exit(EXIT_FAILURE);
	    }
	}

	pch = strtok(NULL, PARSELINE_DELIM);
    }

    tokens[ind] = NULL;
    return tokens;
}
