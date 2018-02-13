/**
 * A user program tha tcalls the getpid system call
 * and gets the pid back.
 */

#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("-------------------\n");
	printf("getpid system call:\n");
	printf("-------------------\n\n");

	// getpid
	int pid = getpid();
	printf("my pid is %d\n", pid);

	printf("\n-------------------\n");
	return 0;
}


