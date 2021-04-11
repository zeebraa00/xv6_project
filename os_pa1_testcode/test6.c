#include "types.h"
#include "stat.h"
#include "user.h"

#define NTHREAD 7

void *stack[NTHREAD];
int tid[NTHREAD];
void *retval[NTHREAD];

void *thread(void *arg){
	int i;
	for(i=0;i<10000000;i++);
	thread_exit((void *)uptime());
	return 0;
}

int
main(int argc, char **argv)
{
	int i;

	printf(1, "TEST6: ");

	for(i=0;i<NTHREAD;i++)
		stack[i] = malloc(4096);

	for(i=0;i<NTHREAD;i++){
		tid[i] = thread_create(thread,  0, stack[i]);
		if(tid[i] == -1){
			printf(1, "WRONG\n");
			exit();
		}
	}

	sleep(100);

	for(i=0;i<NTHREAD;i++){
		if(thread_join(tid[i], &retval[i]) == -1){
			printf(1, "WRONG\n");
			exit();
		}
	}

	for(i=0;i<NTHREAD-1;i++){
		if((int)retval[i] > (int)retval[i+1]){
			printf(1, "WRONG\n");
			exit();
		}
	}

	for(i=0;i<NTHREAD;i++)
		free(stack[i]);

	printf(1, "OK\n");

	exit();
}
