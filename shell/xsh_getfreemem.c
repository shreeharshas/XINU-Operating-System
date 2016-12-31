/* xsh_hello.c - xsh_hello */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_hello - input and print the username in a friendly message
 *------------------------------------------------------------------------
 */
shellcmd xsh_getfreemem(int nargs, char *args[]) {
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s NAME\n\n", args[0]);
		printf("Description:\n");
		printf("\tPrints the free memory with the id and the address\n");
		printf("Options:\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}	
	

        
	intmask mask; /* Saved interrupt mask */
	struct memblk *prev, *curr, *leftover;
	mask = disable();
        int countlist=0;

	prev = &memlist;
	curr = memlist.mnext;
	if(curr != NULL){
		while (curr != NULL) { /* Search free list */
        	        printf("Address:%d\tLength:%d\tNumberOfNodes:%d\n", curr, curr->mlength,++countlist);
			curr = curr->mnext;
			restore(mask);
		}
		restore(mask);
		return OK;
	}
	restore(mask);
	return (char *)SYSERR;
}
