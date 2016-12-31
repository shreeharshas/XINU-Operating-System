/* xsh_stackused.c - xsh_stackused */

#include <xinu.h>
	
/*------------------------------------------------------------------------
 * xsh_stackused - get the maximum stack space of the current process
 *------------------------------------------------------------------------
 */
shellcmd xsh_stackused(int nargs, char *args[]) {
	intmask mask;     
	struct procent *current;
	char *temp = NULL;
	char *t2 = NULL;	
	char *lastAddr = NULL;	
	int count=0;	
	mask = disable();	
	current = &proctab[currpid];

	kprintf("\n\nbase:%u\n\n", current->prstkbase);
	kprintf("\n\nlen:%u\n\n", current->prstklen);

	lastAddr = current->prstkbase - current->prstklen;

	kprintf("\n\nlastaddr:%u\n\n", lastAddr);

	temp = current->prstkptr;

kprintf("\n\ntemp before loop:%u\n\n", temp);

	while(temp !=NULL && temp!=lastAddr)
	{
		/*kprintf("\n\ntemp=%u and count=%d before inc while\n\n", temp, count);*/	
		*temp="FFF";
		temp--;
		/*kprintf("\n\ntemp after inc while:%u\n\n", temp);*/
		count++;
		/*kprintf("\n\ntemp=%u and count=%d after inc while\n\n", temp, count);	*/
	}

	kprintf("\n\ntemp after loop:%u\n\n", temp);
        restore(mask);
	return 0;
}
