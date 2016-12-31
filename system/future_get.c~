#include <prodcons.h>

syscall future_get(future *f,int *value)
{
	intmask mask = 	disable();

	if(f->flag == FUTURE_EXCLUSIVE)
	{ 	
		if(f->state == FUTURE_EMPTY)
		{
			f->pid = currpid;
			f->state = FUTURE_WAITING;
                        restore(mask);
                        return OK;
		} 

	
		if(f->state == FUTURE_VALID)
		{
			*value = *(f->value);
			f->state = FUTURE_EMPTY;
			restore(mask);
			return OK;
		}

	}



	else if ( f->flag == FUTURE_SHARED )
	{

		if ( (f->state == FUTURE_EMPTY) || (f->state == FUTURE_WAITING) )
		{
			f->pid = currpid;
			f->state = FUTURE_WAITING;
			cEnqueue(currpid,&(f->get_queue));
			suspend(currpid);
		}
		
                if(f->state == FUTURE_VALID)
		{
			*value = *(f->value);
			restore(mask);
			return OK;
		}
		
		restore(mask);
		return SYSERR;
	}


	else if ( f->flag == FUTURE_QUEUE )
	{
		if ( (f->state == FUTURE_EMPTY) || (f->state == FUTURE_WAITING) )
		{
			if(cIsEmpty(&(f->set_queue)) == 1)
			{
				f->pid = currpid;
				f->state = FUTURE_WAITING;
				cEnqueue(currpid,&(f->get_queue));
				suspend(currpid);	
			}

		}
		if(f->state == FUTURE_VALID)
		{
			*value = *(f->value);

			resched_cntl(DEFER_START);
			if(			cIsEmpty(&(f->set_queue)) == 0) {
				ready(cDequeue(&(f->set_queue)));
			}
			resched_cntl(DEFER_STOP);

			f->state = FUTURE_EMPTY;
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
	restore(mask);
	return SYSERR;
}


