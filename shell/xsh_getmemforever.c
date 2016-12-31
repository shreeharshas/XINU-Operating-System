/* xsh_getmemforever.c - xsh_getmemforever */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
syscall	getavailablemem()
	 
{	
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
	
/*------------------------------------------------------------------------
 * xsh_getmemforever - Allocate memory permanently to heap and stack
 *------------------------------------------------------------------------
 */
shellcmd xsh_getmemforever(int nargs, char *args[]) {
intmask mask;
        struct TestMemory {
    int *data;
    char size;
         };
	mask = disable();
        printf("\nMemory available before heap allocation\n");
        getavailablemem();
printf("\n");
	struct TestMemory *retVal = getmemForEver(sizeof(struct TestMemory));
        printf("\nMemory available after allocation\n");
        getavailablemem();
        restore(mask);
	return 0;
}
