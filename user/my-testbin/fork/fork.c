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
	if (pid < 0) {
    	warn("fork");
  	}
  	else if (pid == 0) {
	    /* child */
	    putchar('C');
	    putchar('\n');
  	}
  	else {
	    /* parent */
	    putchar('P');
	    putchar('\n');
  	}
  	return 0;
}
