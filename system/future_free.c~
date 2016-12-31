#include <prodcons.h>
syscall future_free(future* f)
{
	freemem(f->value,sizeof(int));
	freemem(f,sizeof(f));
	return OK;
}

