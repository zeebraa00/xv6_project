#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_getnice(void)
{
  int pid;
  if (argint(0, &pid) < 0) return -1;

  return getnice(pid);
}

int
sys_setnice(void)
{
  int pid, var;
  if (argint(0, &pid) < 0 || argint(1, &var) < 0) return -1;

  return setnice(pid, var);
}

int
sys_yield(void)
{
  if (myproc()->pid > 2) {
    myproc()->is_yield = 1;
  }
  yield();
  return 0;
}

int
sys_shout(void) {
  shout();
  return 0;
}

int
sys_ps(void) {
  procdump();
  return 0;
}

int
sys_thread_create(void)
{
  int func, arg, stack;
  if (argint(0, &func) < 0 || argint(1, &arg) < 0 || argint(2, &stack) < 0)
    return -1;

  return thread_create((void*)(func), (void *)arg, (void *)stack);
}

int
sys_thread_join(void)
{
  void **retval;
  int tid;
  if (argint(0, &tid) < 0 || argint(1, (int*)&retval) < 0)
    return -1;

  return thread_join(tid, retval);
}

int
sys_thread_exit(void)
{
  void *retval;
  if (argint(0, (int*)&retval) < 0) return -1;

  thread_exit(retval);
  return 1;
}

int
sys_gettid(void)
{
  return gettid();
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  myproc()->sz+=n;
  // if(growproc(n) < 0)
  //   return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
