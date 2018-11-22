#include <stdio.h>
#include "read.h"

void exec_read(char **args, int len)
{
	int i = 0;
	for (; i < len; i++)
		printf("%s\n", args[i]);
}
