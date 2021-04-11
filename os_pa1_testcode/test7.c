#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NTHREAD 7

void *stack[NTHREAD];
int tid[NTHREAD];
void *retval[NTHREAD];

void *thread1(void *arg){
	int *fd = (int *)arg;

	*fd = open("testfile", O_CREATE|O_RDWR);
	if(*fd < 0){
		printf(1, "WRONG7\n");
		exit();
	}

	if(write(*fd, "hello", 5) != 5){
		printf(1, "WRONG8\n");
		exit();
	}

	thread_exit(0);
	return 0;
}

void *thread2(void *arg){
	int fd = (int)arg;

	if(write(fd, "world", 5) != 5){
		printf(1, "WRONG9\n");
		exit();
	}

	close(fd);

	thread_exit(0);
	return 0;
}

int
main(int argc, char **argv)
{
	int i;
	int fd;
	char buf[100];

	printf(1, "TEST7: ");

	for(i=0;i<NTHREAD;i++)
		stack[i] = malloc(4096);

	if((tid[0] = thread_create(thread1, (void *)&fd, stack[0])) == -1){
		printf(1, "WRONG1\n");
		exit();
	}
	if(thread_join(tid[0], &retval[0]) == -1){
		printf(1, "WRONG2\n");
		exit();
	}
	if((tid[1] = thread_create(thread2, (void *)fd, stack[1])) == -1){
		printf(1, "WRONG3\n");
		exit();
	}
	if(thread_join(tid[1], &retval[1]) == -1){
		printf(1, "WRONG4\n");
		exit();
	}

	fd = open("testfile", O_RDONLY);
	if(read(fd, buf, 10) != 10){
		printf(1, "WRONG5\n");
		exit();
	}

	if(strcmp(buf, "helloworld") != 0){
		printf(1, "WRONG6\n");
		exit();
	}

	for(i=0;i<NTHREAD;i++)
		free(stack[i]);

	printf(1, "OK\n");

	exit();
}
