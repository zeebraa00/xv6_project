#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char *argv[])
{
	int parent = getpid();
	int child;
	
	if ((child = fork()) == 0)
	{
		setnice(parent, 5);	
	}
	else
	{
		setnice(child, 10);
		if (getnice(parent) != 5)
			printf(1, "ERROR!!");
		else if (getnice(child) != 10) 
			printf(1, "ERROR!!");
		else
		{
			printf(1, "Parent: %d\n", getnice(parent));
			printf(1, "Child: %d\n", getnice(child));
		}
		wait();
	}
	exit();
}
