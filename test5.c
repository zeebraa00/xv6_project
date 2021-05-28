#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv){
	int child, parent = getpid();

	if((child = fork()) == 0) { 
		printf(1, "\t<<state2>>\n");
		if(fork() == 0) 
		{
			printf(1, "\t<<state4>>\n");
			setnice(parent, 18);
			printf(1, "\t<<state10>>\n");
			yield();
		} 
		else 
		{
			printf(1, "\t<<state3>>\n");
			yield();
			
			printf(1, "\t<<state8>>\n");
			if(fork() == 0)
			{
				printf(1, "\t<<state11>>\n");
			}
			else
			{
				printf(1, "\t<<state9>>\n");
				wait();
			}
			wait();
		}
	}
	else {
		printf(1, "\t<<state1>>\n");
		setnice(child, 19);
		printf(1, "\t<<state5>>\n");

		if(fork() == 0) 
		{
			printf(1, "\t<<state7>>\n");
			if(fork() == 0)	setnice(getpid(), 20);
			else	wait();
		} 
		else
		{
			printf(1, "\t<<state6>>\n");
			wait();
		}
		wait();
	}
	exit();
}
