#include <prodcons.h>

// To Enqueue an integer
void cEnqueue(pid32 idVal, struct CustQ *qObj) {
    struct CustQEnt *temp;
	temp = (struct CustQEnt*)getmem(sizeof(struct CustQEnt));

	temp->next = (void*)0;
	temp->val = idVal;
    if ((qObj->head == NULL) && (qObj->tail == NULL))
    {
        qObj->qEntCount = 0;
        qObj->tail = qObj->head = temp;
        (qObj->qEntCount)++;
    }
    else
    {
        qObj->tail->next = temp;
        qObj->tail = qObj->tail->next;
        (qObj->qEntCount)++;
    }

}



// To Dequeue an integer.
pid32 cDequeue(struct CustQ *qObj) {

	struct CustQEnt* temp = qObj->head;
	pid32 retVal;

	if(qObj->head == NULL) {
		return -1;

	} else if(qObj->head == qObj->tail) {
		qObj->head = qObj->tail = NULL;

	} else {
		qObj->head = qObj->head->next;
	}
	retVal = temp->val;
	freemem(temp, sizeof(struct CustQ));
        (qObj->qEntCount)--;

	return retVal;
}


void cQPrint(struct CustQ *qObj) {
	struct CustQEnt* temp = qObj->head;
	while(temp != NULL) {
		printf("%d  ",temp->val);
		temp = temp->next;
	}
	printf("\n");
}

int cIsEmpty(struct CustQ *qObj) {
	if ((qObj->head == NULL) && (qObj->tail == NULL))
        return 1; // true
    else
       return 0; // false
}


