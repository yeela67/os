/**
 * A user program tha tcalls the getpid system call
 * and gets the pid back.
 */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

int main(void) {
	// getpid
	pid_t pid = getpid();
	char c = pid + '0';
   	putchar(c);
	return 0;
}


