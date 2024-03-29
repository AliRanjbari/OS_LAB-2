#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
  if(growproc(n) < 0)
    return -1;
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


// find next prime number
int
sys_find_next_prime_num(void)
{
  int a = myproc()->tf->ebx; //register after eax
  cprintf("in kernel systemcall sys_find_next_prime_num() called for number %d\n", a);
  return find_next_prime_num(a);
}

// get parent proc id
int
sys_get_call_count(void)
{

  int sys_call_num;
  if(argint(0, &sys_call_num) < 0)
    return -1;
  return get_call_count(sys_call_num);
}

// get most caller
int
sys_get_most_caller(void)
{

  int sys_call_num;
  if(argint(0, &sys_call_num) < 0)
    return -1;
  return get_most_caller(sys_call_num);
}


// wait for process
void
sys_wait_for_process(void)
{

  int pid;
  argint(0, &pid);
  wait_for_process(pid);

}