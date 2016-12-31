#include <prodcons.h>

syscall future_cons(future *fut) {int i, status;
	intmask mask;
	mask = disable();
	status = future_get(fut, &i);
	if (status == OK) {

		printf("\nconsumed : %d\n", i);

		// TODO: free future memory in the main function, when all are consumed

		restore(mask);
		return status;

	} else {
		printf("Not able to fetch value");
		future_free(fut);
		restore(mask);
		return status;

	}
}



