#include "types.h"
#include "stat.h"
#include "user.h"

void *thread(void *arg){
	thread_exit((void *)0x87654321);
	return 0;
}

int
main(int argc, char **argv)
{
	void *stack;
	int tid;
	void *retval;

	printf(1, "TEST2: ");

	stack = malloc(4096);
	
	tid = thread_create(thread, (void *)0x12345678, stack);
	if(tid == -1){
		printf(1, "WRONG1\n");
		exit();
	}

	if(thread_join(tid, &retval) == -1){
		printf(1, "WRONG2\n");
		exit();
	}

	if(retval != (void *)0x87654321){
		printf(1, "WRONG3\n");
		exit();
	}

	free(stack);

	printf(1, "OK\n");

	exit();
}
