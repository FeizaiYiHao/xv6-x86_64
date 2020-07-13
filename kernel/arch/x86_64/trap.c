#include "../../types.h"
#include "../../defs.h"
#include "../../param.h"
#include "proc.h"
#include "x86_64.h"
#include "traps.h"
#include "../../spinlock.h"

// Interrupt descriptor table (shared by all CPUs).
/* TODO: uncomment
struct intgate idt[256];
extern uint64 vectors[];  // in vectors.S: array of 256 entry pointers
*/
struct spinlock tickslock;
uint ticks;

void
trapinit(void)
{
  /* TODO: uncomment
  int i;

  for(i=0; i<256; i++) {
    idt[i] = INTDESC(KCSEG, vectors[i], INT_P | SEG_INTR64);
  }
  idtinit();
  */

  initlock(&tickslock, "time");
}

/* TODO: uncomment
void
idtinit(void)
{
  struct desctr dtr;

  dtr.limit = sizeof(idt) - 1;
  dtr.base = (uint64)idt;
  lidt((void *)&dtr.limit);
}
*/

//PAGEBREAK: 41
void
trap(struct trapframe *tf)
{
  if(tf->trapno == T_SYSCALL){
    if(myproc()->killed)
      /* TODO: uncomment */
      panic("commented exit();");
    myproc()->tf = tf;
    /* TODO: uncomment */
    panic(" commented syscall();");
    if(myproc()->killed)
      /* TODO: uncoment */
      panic("commented exit();");
    return;
  }

  /* TODO: uncomment
  switch(tf->trapno){
  case T_IRQ0 + IRQ_TIMER:
    if(cpuid() == 0){
      acquire(&tickslock);
      ticks++;
      wakeup(&ticks);
      release(&tickslock);
    }
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE:
    ideintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE+1:
    // Bochs generates spurious IDE1 interrupts.
    break;
  case T_IRQ0 + IRQ_KBD:
    kbdintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_COM1:
    uartintr();
    lapiceoi();
    break;
  case T_IRQ0 + 7:
  case T_IRQ0 + IRQ_SPURIOUS:
    cprintf("cpu%d: spurious interrupt at %x:%x\n",
            cpuid(), tf->cs, tf->rip);
    lapiceoi();
    break;

  //PAGEBREAK: 13
  default:
    if(myproc() == 0 || (tf->cs&3) == 0){
      // In kernel, it must be our mistake.
      cprintf("unexpected trap %d from cpu %d eip %x (cr2=0x%x)\n",
              tf->trapno, cpuid(), tf->rip, rcr2());
      panic("trap");
    }
    // In user space, assume process misbehaved.
    cprintf("pid %d %s: trap %d err %d on cpu %d "
            "eip 0x%x addr 0x%x--kill proc\n",
            myproc()->pid, myproc()->name, tf->trapno,
            tf->err, cpuid(), tf->rip, rcr2());
    myproc()->killed = 1;
  }

  // Force process exit if it has been killed and is in user space.
  // (If it is still executing in the kernel, let it keep running
  // until it gets to the regular system call return.)
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();

  // Force process to give up CPU on clock tick.
  // If interrupts were on while locks held, would need to check nlock.
  if(myproc() && myproc()->state == RUNNING &&
     tf->trapno == T_IRQ0+IRQ_TIMER)
    yield();
  
  // Check if the process has been killed since we yielded
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();
    */
}
