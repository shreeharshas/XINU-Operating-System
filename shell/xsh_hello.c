/* xsh_hello.c - xsh_hello */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_hello - input and print the username in a friendly message
 *------------------------------------------------------------------------
 */
shellcmd xsh_hello(int nargs, char *args[]) {

	//int32	retval;			/* return value			*/
	//uint32	now;			/* current local time		*/
	//char	datestr[64];		/* printable date in ascii	*/

	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s NAME\n\n", args[0]);
		printf("Description:\n");
		printf("\tAccepts and prints the username with a message\n");
		printf("Options:\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	/* Check argument count */

	else if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
		return 1;
	}

	else if (nargs < 2) {
		fprintf(stderr, "%s: too few arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
		return 1;
	}

	if (nargs == 2) 
	{
		printf("Hello %s, Welcome to the world of Xinu!\n\n", args[1]);
		return 1;		
	}	
	return 0;
}
