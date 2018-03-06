/**
 * A simple user program that:
 * 1. Calls the fork system call
 * 2. Prints out the pid returned from the call
 *
 * 3. Tests the waitpid system call
 * 4. Tests the getpid system call
 */

#include <stdio.h>
#include <unistd.h>

int main(void) {
	int pid = 1;

	pid = getpid();
	putchar(pid)

	pid = waitpid(pid, 0, -1);
	putchar(pid);


	pid = fork();
	putchar(pid);

	return 0;
}

