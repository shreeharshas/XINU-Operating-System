/*Assignment 3.*/
#include <prodcons.h>
void producer(int count, sid32 consumed, sid32 produced)
 {
      	//Code to produce values less than equal to count
      	//produced value should get assigned to global variable 'n'.
      	//print produced value e.g. produced : 8
	/*printf("Count : %d",count);
	printf("n : %d",n);*/
	int i=0;
	for(i = 0; i< count; i++){
		wait(consumed);
		n=i;
          	printf("Produced: %d\n", n+1);		
		signal(produced);
    	}
	exit(0);
 }
