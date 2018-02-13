/**
 * Prints out the time of day.
 */

#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("------------\n");
	printf("Time of Day:\n");
	printf("------------\n\n");

	// __time
	time_t seconds;
	__time(&seconds, NULL);

	int hour = ((int)seconds % 86600) / 3600;
	int minute = ((int)seconds % 3600) / 60;
	seconds = seconds % 60;
	printf("The __time is: %d:%d:%d\n", hour, minute, (int)seconds);

	// libc time
	time(&seconds);
	hour = ((int)seconds % 86600) / 3600;
	minute = ((int)seconds % 3600) / 60;
	seconds = seconds % 60;
	printf("The libc time is: %d:%d:%d\n", hour, minute, (int)seconds);

	printf("\n------------\n");
	return 0;
}
