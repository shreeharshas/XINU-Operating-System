/* kill.c - kill */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	int32	i, maxusedcount=0;			/* Index into descriptors	*/

	char * temp=NULL;

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	/* printf("\n\n\nMax Stack Length: %u \n\n prstkbase: %u \n\n difference %u", prptr->prstklen, prptr->prstkbase, prptr->prstkbase - 168471209);*/
if (strncmp(prptr->prname,"getmemforever",8) != 0){
if (strncmp(prptr->prname,"stackused",8) == 0){
	temp = prptr->prstkbase;
kprintf("\n temp in kill %u ",temp);

	while((unsigned)*temp!= 4){

		maxusedcount++;
               temp--;
	}

kprintf("\nmaxusedcount= %u\n\n",maxusedcount);
}
	freestk(prptr->prstkbase, prptr->prstklen);
}
else{
kprintf("\nCurrent process stack memory won't be freed\n");
}

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}
