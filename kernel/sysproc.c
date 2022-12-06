#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sysinfo.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// student code
// sys_trace
//
uint64
sys_trace(void)
{
	int mask;
	argint(0,&mask);
	printf("sys_trace: hi, %d execute successfully\n",mask);
	
	struct proc *p = myproc();
	p->trace_mask = mask;
	return 0;
}

uint64 sys_sysinfo(void)
{
	uint64 addr;
	argaddr(0,&addr);
	struct sysinfo sf;
	sf.nproc = nop();//nop 后面加
	sf.freemem = freemem();// 后面加
	if (copyout(myproc()->pagetable,addr,(char*)&sf,sizeof(sf)) < 0)
		return -1;
	return 0;
}

int
sys_pgaccess(void)
{
	uint64 start_addr;	// 测试程序中buf的地址
	int amount;			// ........32
	uint64 buffer;		// ........abits的地址
	argaddr(0,&start_addr);
	argint(1,&amount);
	argaddr(2,&buffer);
	//获取三个参数
	struct proc* p = myproc();
	uint64 mask = access_check(p->pagetable,start_addr); // 页表是当前进程的页表
	if (copyout(p->pagetable,buffer,(char*)&mask,sizeof(uint64)) < 0)
		return -1;
	return 0;
}
