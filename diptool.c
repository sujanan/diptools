#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "diptool.h"
#include "read.h"

const char *prompt_string = "[diptool]";

static size_t read_line(char *buf, size_t len)
{
	int c, i = 0;	
	while ((c = getchar()) != '\n' && c != EOF && i < len - 1)
		buf[i++] = c;
	buf[i] = 0;
	if (i >= len - 1) {
		while ((c = getchar()) != '\n' && c != EOF)
			;
	}
	return i;
}

static char *build_token(char *start, size_t len)
{
	char *token = malloc(len + 1);

	if (token == NULL) {
		fprintf(stderr, "error: %s\n", strerror(errno));
		exit(1);
	}
	strncpy(token, start, len);
	return token;
}

static char **build_tokenarray(char *buf, size_t buflen)
{	
	size_t tokenarray_size = 8;	
	char **tokenarray;
	int i = 0, j = 0, k = 0, tmp = 0;

	/* Skip all heading spaceses */
	while (i < buflen && isspace(buf[i]))
		i++;	
	if (i >= buflen)
		return NULL;

	tokenarray = malloc(sizeof(char *) * tokenarray_size);
	if (tokenarray == NULL)
		goto error;

	while (i < buflen) {
		if (isspace(buf[i])) {
			tmp = i;
			/* Save i before interate through spaceses */
			while (i < buflen && isspace(buf[i]))	
				i++;
			tokenarray[k++] = build_token(buf + tmp - j, j);
			j = 0;
		} else {
			i++;
			j++;
		}
	}
	/* Has a token to proccess */
	if (j != 0)
		tokenarray[k++] = build_token(buf + i - j, j);

	tokenarray[k] = NULL;
	return tokenarray;
error:
	fprintf(stderr, "error: %s\n", strerror(errno));
	exit(1);
}

static void free_tokenarray(char **tokenarray)
{
	if (tokenarray == NULL)
		return;
	int i; 
	
	for (i = 0; tokenarray[i] != NULL; i++)
		free(tokenarray[i]);
	free(tokenarray);
}

static void exec_line(char *buf, size_t buflen)
{
	char **tokenarray = build_tokenarray(buf, buflen);
	free_tokenarray(tokenarray);
}

int main(int argc, char **argv)
{
	size_t bufsize = 1024, buflen;
	char buf[bufsize];

	while (1) {
		printf("%s ", prompt_string);
		memset(buf, 0, bufsize);
		buflen = read_line(buf, bufsize);
		exec_line(buf, buflen);
	}

	return 0;
}
