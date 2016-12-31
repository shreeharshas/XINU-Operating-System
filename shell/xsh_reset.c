/* xsh_reset.c - xsh_reset */
#include <xinu.h>
#include <string.h>
#include <stdio.h>

shellcmd xsh_reset(int nargs, char *args[]) {	
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s\n", args[0]);
		printf("Description:\n");
		printf("\tSoft-resets the XINU system\n");				
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}	

	/* Check argument count */
	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		return 1;
	}
	else{
		volatile uint32 *prm_rstctrl = (volatile uint32 *) 0x44E00F00;
		*prm_rstctrl = 0x01;
		return 0;
	}
	return 0;
}
