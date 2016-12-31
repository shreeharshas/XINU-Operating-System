#include <prodcons.h>

future* future_alloc(int future_flag)
{
	intmask	mask;
	future *f=NULL;
	mask = disable();
	f = getmem(sizeof(future));
	if(f != NULL)
	{
		f->flag = future_flag;
		f->state = FUTURE_EMPTY;

		f->value = getmem(sizeof(int));	

		f->get_queue.head = NULL;		
		f->get_queue.tail = NULL;		
		f->get_queue.qEntCount = 0;

		f->set_queue.head = NULL;
		f->set_queue.tail = NULL;
		f->set_queue.qEntCount = 0;
	}
	else
	{
		restore(mask);
		return f;
	}

	restore(mask);
	return f;
}
