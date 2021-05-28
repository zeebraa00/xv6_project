#include "types.h"
#include "stat.h"
#include "user.h"

int
main (int argc, char **argv)
{
	int child;
	
	if((child = fork()) == 0)
	{
		printf(1, "\t<<state5>>\n");
		if((child = fork()) == 0)
		{
			printf(1, "\t<<state7>>\n");
		}
		else
		{
			printf(1, "\t<<state6>>\n");
			setnice(child, 18);
			printf(1, "\t<<state8>>\n");
			wait();
		}
	}
	else
	{
		setnice(child, 21);
		printf(1, "\t<<state1>>\n");
		
		if ((child = fork()) == 0) 
		{
			printf(1, "\t<<state9>>\n");
		}
		else
		{	
			setnice(child, 22);
			printf(1, "\t<<state2>>\n");

			if((child = fork()) == 0)
			{
				printf(1, "\t<<state4>>\n");
			}
			else
			{
				printf(1, "\t<<state3>>\n");
				setnice(child, 17);
				wait();
			}
			wait();
		}
		wait();
	}
	exit();
}
