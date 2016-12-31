/* xsh_getpmaxstk.c - xsh_getpmaxstk */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_getpmaxstk - get the maximum stack space of the current process
 *------------------------------------------------------------------------
 */
shellcmd xsh_getpmaxstk(int nargs, char *args[]) {

	struct procent current = proctab[currpid];
	/*struct procent *endPtr = proctab + sizeof(proctab)/sizeof(proctab[0]);*/

	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s NAME\n\n", args[0]);
		printf("Description:\n");
		printf("\tPrints the capacity of the current process' stack\n");
		printf("Options:\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	/* Check argument count */

	else if (nargs > 1) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
		return 1;
	}

	if (nargs == 1) 
	{
		
		/*Loop through the proctab*/
/*		while ( current < endPtr ){*/

		/*Find the current process in proctab*/
/*		if (current!=NULL){*/
			/*Print the current process' prstklen*/
			printf("Max Stack Length of current process: %u", current.prstklen);
/*		}			*/
/*ptr++;*/
/*		}	*/	
	}	
	return 0;
}
