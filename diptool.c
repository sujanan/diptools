#include <stdio.h>
#include <string.h>
#include "diptool.h"
#include "read.h"

const char *prompt_string = "[diptool]";

static void read_line(char *buf, size_t len)
{
	int c, i = 0;	
	while ((c = getchar()) != '\n' && c != EOF && i < len - 1)
		buf[i++] = c;
	buf[i] = 0;
	if (i >= len - 1) {
		while ((c = getchar()) != '\n' && c != EOF)
			;
	}
}

static void exec_line(const char *buf, size_t buflen)
{
	int rt;
	
	if (!strcmp(buf, "read"))
		rt = exec_read(buf);
}

int main(int argc, char **argv)
{
	size_t buflen = 10;
	char buf[buflen];

	while (1) {
		printf("%s ", prompt_string);
		memset(buf, 0, buflen);
		read_line(buf, buflen);
		exec_line(buf, buflen);
	}

	return 0;
}
