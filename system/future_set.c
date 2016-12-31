#include <prodcons.h>

syscall future_set(future* f,int* value)
{	
	pid32 p_id = 0; 
        int  count_queue=0;
	intmask mask = 	disable();

	if(f->flag == FUTURE_EXCLUSIVE)
	{	
		if( (f->state == FUTURE_EMPTY)  ||  (f->state == FUTURE_WAITING) )
		{
			*(f->value) = *value;
			f->state = FUTURE_VALID;

			restore(mask);
			return OK;
		}
		restore(mask);
		return SYSERR;
	}



	else if(f->flag == FUTURE_SHARED)
	{
		if( (f->state == FUTURE_EMPTY)  ||  (f->state == FUTURE_WAITING) )
		{
			*(f->value) = *value;
			f->state = FUTURE_VALID;
			resched_cntl(DEFER_START);
			count_queue = f->get_queue.qEntCount;
			while(count_queue >0) {
				p_id = cDequeue(&(f->get_queue));
				ready(p_id);
				--count_queue;
			}
			resched_cntl(DEFER_STOP);

			restore(mask);
			return OK;
		}

		if( f->state == FUTURE_VALID)
		{
			restore(mask);
			return SYSERR;
		}
		restore(mask);
		return SYSERR;
	}





	else if(f->flag == FUTURE_QUEUE)
	{
		if ( f->state == FUTURE_VALID ) 
		{
			f->pid = currpid;
			f->state = FUTURE_VALID;

			cEnqueue(currpid,&(f->set_queue));
			suspend(currpid);
			restore(mask);
			return OK;
		}

		if( (f->state == FUTURE_EMPTY)  ||  (f->state == FUTURE_WAITING) )
		{
			*(f->value) = *value;
			f->state = FUTURE_VALID;

			resched_cntl(DEFER_START);
			if(cIsEmpty(&(f->get_queue)) == 0)
			{
				ready(cDequeue(&(f->get_queue)));
			}
			resched_cntl(DEFER_STOP);
			restore(mask);
			return OK;
		} 

		restore(mask);
		return SYSERR;
	} 
	else 
	{
		restore(mask);
		return SYSERR;
	}
}

