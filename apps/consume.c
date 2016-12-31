/*Assignment 3.*/
#include <prodcons.h>
void consumer(int count, sid32 consumed, sid32 produced)
 {
	//Use system call wait() and signal() with predefined semaphores 
      	//produced and consumed to synchronize critical section
      	//Code to consume values of global variable 'n' until the value
      	//of n is less than or equal to count
      	//print consumed value e.g. consumed : 8
	int i=0;
	for (i = 0; i<= count; i++){
		wait(produced);
          	printf("Consumed: %d\n",n+1);
		signal(consumed);
    	}
	exit(0);
 }
