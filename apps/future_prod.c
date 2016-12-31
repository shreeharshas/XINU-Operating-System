#include <prodcons.h>
int getval_udp(int val)
{
	int	i;			/* index into buffer		*/
	int	retval;			/* return value			*/
	char	msg[100]; /* message to send	*/
	char	inbuf[1500];		/* buffer for incoming reply	*/
	int32	slot;			/* UDP slot to use		*/
	int32	msglen;			/* length of outgoing message	*/
	uint32	remoteip;		/* remote IP address to use	*/
	//uint32	localip;		/* local IP address to use	*/
	uint16	echoport= 4121;		/* port number for UDP echo	*/
	uint16	locport	= 52743;	/* local port to use		*/
	int32	retries	= 3;		/* number of retries		*/
	int32	delay	= 2000;		/* reception delay in ms	*/
        int recvVal;



if (dot2ip("192.168.1.100", &remoteip) == SYSERR) {
		fprintf(stderr, "invalid IP address argument\r\n");
		return 1;
	}
sprintf(msg,"%d",val);
	/* register local UDP port */

	slot = udp_register(remoteip, echoport, locport);
	if (slot == SYSERR) {
		return val;
	}

	/* Retry sending outgoing datagram and getting response */

	msglen = strnlen(msg, 1200);
	for (i=0; i<retries; i++) {
		retval = udp_send(slot, msg, msglen);
		if (retval == SYSERR) {
			return 1;
		}

 		retval = udp_recv(slot, inbuf, sizeof(inbuf), delay);


		if (retval == TIMEOUT) {
			fprintf(stderr, "timeout...\n");
			continue;
		} else if (retval == SYSERR) {
			udp_release(slot);
			return 1;
		}
		break;
	}

	udp_release(slot);
	if (retval == TIMEOUT) {
		fprintf(stderr, "retry limit exceeded\n");
		return 1;
	}

	/* Response received - check contents */

	if (retval != msglen) {
		return 1;
	}
	for (i = 0; i < msglen; i++) {
		if (msg[i] != inbuf[i]) {
			return 1;
		}
	}

	//printf("UDP echo test was successful\n");

//sscanf(&recvVal, "%d", inbuf);
recvVal = atoi(inbuf);
//kprintf("\recvVal:%d\n", recvVal);
	return recvVal;
}




syscall future_prod(future *fut, int num) {
  int i, j;
  int status;

  j = (int)fut;
  for (i=0; i<20;i++) {
       j=getval_udp(i);
//kprintf("\nj:%d\n",j);
  }


  status = future_set(fut, &j);
  return status;
}

