#include <future.h>
/*Global variable for producer consumer*/
extern int n; /*this is just declaration*/

/*function Prototype*/
void consumer(int, sid32, sid32);
void producer(int, sid32, sid32);
syscall future_prod(future *fut,int);
syscall future_cons(future *fut);

/* Semaphore Declarations */
extern sid32 produced, consumed; /* Assignment 3 addition */
