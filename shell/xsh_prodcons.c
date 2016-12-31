/*Assignment 4.*/
#include <prodcons.h>
#include <stdbool.h>
#include <ctype.h>
/*Global variables declaration*/
int n;
sid32 produced, consumed;       
future *f_exclusive, *f_shared, *f_queue;

bool isNumber(char number[])
{
	const int len = strlen(number);
	int i = 0;
	for (i = 0; i < len; i++){
        	if (!isdigit(number[i])){
            		return false;
         	}
    	}
	return true;
}

shellcmd xsh_prodcons(int nargs, char *args[]){
  	int count = 2000;             //local varible to hold count
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s NAME\n\n", args[0]);
		printf("Description:\n");
		printf("\tAccepts and prints the username with a message\n");
		printf("Options:\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	else if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
		return 1;
	}
	
	if (nargs == 2){
		if(isNumber(args[1])){			//Argument verifications and validations
			count = atoi(args[1]);
  			produced = semcreate(0);
                        consumed = semcreate(1);
  			//create the process producer and consumer and put them in ready queue.     
  			resume( create(producer, 1024, 20, "producer", 3, count, consumed, produced));
  			resume( create(consumer, 1024, 20, "consumer", 3, count, consumed, produced));
  			/*semdelete(0);
			semdelete(1);*/
			return 0;
                }
            
                else{
                      if (strncmp(args[1], "-f", 3) == 0){
                           f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
                           f_shared = future_alloc(FUTURE_SHARED);
                           f_queue = future_alloc(FUTURE_QUEUE);
 
               // Test FUTURE_EXCLUSIVE
                  resume( create(future_prod, 1024, 20, "fprod1", 2, f_exclusive, 10) );
                  resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
                  

		// Test FUTURE_SHARED
                  resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
                  resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
                  resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
                  resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
                  resume( create(future_prod, 1024, 20, "fprod2", 2, f_shared, 20) );

		// Test FUTURE_QUEUE
                  resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
                  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
                  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
                  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
                  resume( create(future_prod, 1024, 20, "fprod3", 2, f_queue, 30) );
                  resume( create(future_prod, 1024, 20, "fprod4", 2, f_queue, 31) );
                  resume( create(future_prod, 1024, 20, "fprod5", 2, f_queue, 32) );
                  resume( create(future_prod, 1024, 20, "fprod6", 2, f_queue, 33) );

                 }
                      else{printf("Invalid input, please type %s --help for details\n", args[0]);}
						
                }

	}

	else if (nargs < 2){
                        printf("----Using Semaphores,not future\n");
  			produced = semcreate(0);
                        consumed = semcreate(1);
  			//create the process producer and consumer and put them in ready queue.     
  			resume( create(producer, 1024, 20, "producer", 3, count, consumed, produced));
  			resume( create(consumer, 1024, 20, "consumer", 3, count, consumed, produced));

	}
	return (0);
}
