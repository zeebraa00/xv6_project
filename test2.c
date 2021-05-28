#include "types.h"
#include "stat.h"
#include "user.h"

int
main (int argc, char **argv)
{
	int child, parent = getpid();
	if((child = fork()) == 0)
	{
		printf(1, "\t<<state2>>\n");
		if((child = fork()) == 0)
		{
			printf(1, "\t<<state4>>\n");
			setnice(parent, 1);
			printf(1, "\t<<state6>>\n");
		}
		else
		{
			printf(1, "\t<<state3>>\n");
			wait();
		}
	}
	else
	{
		printf(1, "\t<<state1>>\n");
		setnice(child, 10);
		printf(1, "\t<<state5>>\n");
		wait();
	}
	exit();
}
