#include<xinu.h>

struct CustQEnt {
	pid32 val;
	struct CustQEnt *next;
};

struct CustQ {
	struct CustQEnt *head;
	struct CustQEnt *tail;
	int qEntCount;
};

// To Enqueue an integer
void cEnqueue(pid32 idVal, struct CustQ *qObj);

// To Dequeue an integer.
pid32 cDequeue(struct CustQ *qObj);

int cIsEmpty(struct CustQ *qObj);

void cQPrint(struct CustQ *qObj);


