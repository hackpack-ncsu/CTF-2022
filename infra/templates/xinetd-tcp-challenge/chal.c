#include <stdio.h>

#ifndef FLAG_STRING
#	define FLAG_STRING "flag{th1s_1$_my_1st_ch@ll3ng3}"
#endif

const char *FLAG = FLAG_STRING;

int
main(int argc, char **argv) {
	// turn off all output buffering to avoid needing to flush after line-writes
	// (sockets do not autoflush on LF like TTYs do...)
	setvbuf(stdout, NULL, _IONBF, 0);

	puts("welcome to mY fIRST cHALLENGE!");
	for (;;) {
		int x = -1;
		fputs("enter a number: ", stdout);
		/* ***BUG!*** if you enter, e.g., "fred" instead of an integer, this program will go
		 * into an infinite loop!  Easy enough to break out of at a TTY (CTRL-c), but what
		 * about when its running under xinetd? Well then the server's CPU starts spiking and
		 * the contest admins start running around with their hair on fire!
		 *
		 * So don't do this (see the commented-out alternative with proper error handling below
		 * */
		scanf(" %d", &x);

		/*
		// error-handling version of the above
		if (scanf(" %d", &x) != 1) {
			printf("hey, that's messed up---no more challenge for you!!\n");
			return 1;
		}
		// */

		if (x == 42) {
			printf("hey, you guessed the answer! flag: %s\n", FLAG);
			return 0;
		} else {
			printf("sorry, %d is not the answer to Life, the Universe, and Everything...\n", x);
		}
	}
}
