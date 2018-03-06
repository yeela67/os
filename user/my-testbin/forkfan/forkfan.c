/**
 * A simple fork fan.
 */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

int main(void) {
   pid_t childpid;
   for (int i = 1; i < 5; i++) {
   	if ((childpid = fork()) <= 0) {
   		break;
   	}
		char c = childpid + '0';
   	putchar(c);
   	putchar('\n');
   }
   return 0;
}
