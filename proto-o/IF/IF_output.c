#include <stdio.h>

int IF_output(char *str){
	printf("\x1b[36m");
	printf("%s\n", str);
	printf("\x1b[39m");
	return 0;
}
