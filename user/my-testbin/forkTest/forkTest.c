/**
 * Simple fork test.
 */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

int main(void) {
	pid_t pid;
	pid = fork();
	char c = pid + '0';
	if (pid < 0) {
    	warn("fork");
  	}
  	else if (pid == 0) {
	    /* child */
	    putchar(c);
	    putchar('\n');
  	}
  	else {
	    /* parent */
	    putchar(c);
	    putchar('\n');
  	}
  	return 0;
}
