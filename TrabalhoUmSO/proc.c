#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"



struct {
  struct spinlock lock;
  struct proc procBloq[NPROC];
  struct proc proc[NPROC];
} ptable;

static struct proc *initproc;

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

void teste(int vl){
	if (vl == 1)
		cprintf("\n ----------->UM<--------------\n");
	if (vl == 2)
		cprintf("\n ----------->DOIS<--------------\n");
	if (vl == 3)
		cprintf("\n ----------->TRES<--------------\n");
	if (vl == 4)
		cprintf("\n ----------->QUATRO<--------------\n");
	if (vl == 5)
		cprintf("\n ----------->CINCO<--------------\n");		
	
}
/*
void organize(int table){
	struct proc *p, *pTemp, *pAux;
	// 0 - coloca na ultima posição da tabela de processos bloqueados.
	if (table == 0){
		for(p = ptable.procBloq; p < &ptable.procBloq[NPROC]; p++){
			if (p == process){
				ptable.procBloq[NPROC] = NULL;
			}
		}
	}
	if (table == 1){
		p, pTemp = ptable.proc;
		p++; // p sempre vai estar uma posição a frente do pTemp;
		for(; p < &ptable.proc[NPROC]; p++, pTemp++){
			if (pTemp->state == UNUSED && p->state != UNUSED){
				// endereço atual é guardado temporariamente.
				pAux = pTemp;
				// atual recebe o próximo processo.
				pTemp = p;
				// Próximo processo recebe endereço sem processo.
				p = pAux;
			}
		}
	}
}
*/

void swapProc(int state, struct proc *process ){
	struct proc *p, *pBloq, *pAux;
	int i = 0;
	int j = 0;
	
	if (state == UNUSED){
		cprintf("\n ----------->UNUSED<--------------");
		cprintf(" swapProc nr:%d, %s, %d", process->pid, process->name, process->state); //apagar
	}
	if (state == EMBRYO){
		cprintf("\n ----------->EMBRYO<--------------");
		cprintf(" swapProc nr:%d, %s, %d", process->pid, process->name, process->state); //apagar
	}
	if (state == SLEEPING){
		for(p = ptable.proc; i < NPROC; p++, i++){
			cprintf("\n swapProc primeiro nr:%d, %s, %d, i: %d", process->pid, process->name, process->state, i); //apagar
			if (p->pid == process->pid && strcmp(p->name, "initcode") != 0){
				cprintf("\n swapProc primeiro dentro if nr:%d, %s, %d", process->pid, process->name, process->state); //apagar
				for(pBloq = ptable.procBloq; j < NPROC; pBloq++, j++){
					
					cprintf("\n swapProc Segundo nr:%d, %s, %d, i: %d", process->pid, process->name, process->state, j); //apagar
					if (pBloq->state == UNUSED){
						cprintf("\n swapProc Segundo dentro do if nr:%d, %s, %d", process->pid, process->name, process->state); //apagar
						pAux = pBloq;
						pBloq = p;
						p = pAux;
						//organize(1);
						//cprintf("\n -------AAA---->FUNCIO----------");
						//cprintf(" swapProc SLEEPING nr:%d, %s, %d", process->pid, process->name, process->state); //apagar
						break;
					}	
				}
				break;
			}
		
		}
	}
	if (state == RUNNABLE){
		for(pBloq = ptable.procBloq; pBloq < &ptable.procBloq[NPROC]; pBloq++){
			if (pBloq->pid == process->pid){
				for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
					if (p->state == UNUSED){
						pAux = p;
						p = p;
						pBloq = pAux;
						//organize(1);
						cprintf("\n -------AAA---->FUNCIO----------");
						cprintf(" swapProc RUNNABLE nr:%d, %s, %d", process->pid, process->name, process->state); //apagar
						continue;
					}	
				}
				continue;
			}
		}
	}
	if (state == RUNNING){
		cprintf("\n ----------->RUNNING<--------------");
		cprintf(" swapProc nr:%d, %s, %d", process->pid, process->name, process->state); //apagar
	}
	if (state == ZOMBIE){
		cprintf("\n ----------->ZOMBIE<--------------");
		cprintf(" swapProc nr:%d, %s, %d", process->pid, process->name, process->state); //apagar
	}
		
	//struct proc *p;
	//acquire(&ptable.lock);
	if (state == 0){
		//for(p = ptable.proc; a < NPROC; p++, a++){
			//cprintf("\n allocproc nr:%d, %s, %d", p->pid, p->name, p->state); //apagar
	}
	if (state == 1){
		//for(p = ptable.proc; a < NPROC; p++, a++){
			//cprintf("\n allocproc nr:%d, %s, %d", p->pid, p->name, p->state); //apagar
	}
	//cprintf("\n allocproc nome bloqueio: %s", ptable.lock.name); //apagar
	
	//release(&ptable.lock);

  //for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    //if(p->state == UNUSED)
      //goto found;
  //release(&ptable.lock);
	
} 

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;	
  int a=0;
  acquire(&ptable.lock);
  //cprintf("\n allocproc nome bloqueio: %s", ptable.lock.name); //apagar
  for(p = ptable.proc; a < NPROC; p++, a++){
	cprintf("\n allocproc nr:%d, %s, %d", p->pid, p->name, p->state); //apagar
}
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;
  release(&ptable.lock);
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;
  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;
  
  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;
  
  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];
  
  p = allocproc();
  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  p->state = RUNNABLE;
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  
  sz = proc->sz;
  if(n > 0){
    if((sz = allocuvm(proc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(proc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  proc->sz = sz;
  switchuvm(proc);
  return 0;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;

  // Allocate process.
  if((np = allocproc()) == 0)
    return -1;

  // Copy process state from p.
  if((np->pgdir = copyuvm(proc->pgdir, proc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = proc->sz;
  np->parent = proc;
  *np->tf = *proc->tf;

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(proc->ofile[i])
      np->ofile[i] = filedup(proc->ofile[i]);
  np->cwd = idup(proc->cwd);

  safestrcpy(np->name, proc->name, sizeof(proc->name));
 
  pid = np->pid;

  // lock to force the compiler to emit the np->state write last.
  acquire(&ptable.lock);
  np->state = RUNNABLE;
  release(&ptable.lock);
  
  return pid;
}

// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
void
exit(void)
{
  struct proc *p;
  int fd;

  if(proc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(proc->ofile[fd]){
      fileclose(proc->ofile[fd]);
      proc->ofile[fd] = 0;
    }
  }

  begin_op();
  iput(proc->cwd);
  end_op();
  proc->cwd = 0;

  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(proc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == proc){
      p->parent = initproc;
      if(p->state == ZOMBIE)
        wakeup1(initproc);
    }
  }

  // Jump into the scheduler, never to return.
  proc->state = ZOMBIE;
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid;

  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for zombie children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != proc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->state = UNUSED;
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || proc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(proc, &ptable.lock);  //DOC: wait-sleep
  }
}

//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void
scheduler(void)
{
  struct proc *p;
  //int a;

  for(;;){
    // Enable interrupts on this processor.
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    //for(p = ptable.proc, a = 0; a < NPROC; p++, a++){
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state != RUNNABLE)
        continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      proc = p;
      switchuvm(p);
      p->state = RUNNING;
      swtch(&cpu->scheduler, proc->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      proc = 0;
      //break;
    }
    release(&ptable.lock);

  }
}

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state.
//Troca de contexto de processo que esta na cpu
void
sched(void)
{
  int intena;
	
  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(cpu->ncli != 1)
    panic("sched locks");
  if(proc->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = cpu->intena;
  cprintf("\n sched entrou2 nr:%d, %s, %d", proc->pid, proc->name, proc->state); //apagar
  swtch(&proc->context, cpu->scheduler);
  cprintf("\n sched saiu nr:%d, %s", proc->pid, proc->name); //apagar
  cpu->intena = intena;
  cprintf("\n sched saiu1 nr:%d, %s, %d", proc->pid, proc->name, proc->state); //apagar
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  //cprintf("\nyield antes nr:%d, %s, %d", proc->pid, proc->name, proc->state); //apagar
 
  acquire(&ptable.lock);  //DOC: yieldlock
  proc->state = RUNNABLE;
  //teste(4);//apagar
  cprintf("\n yield ANTES nr:%d, %s, %d", proc->pid, proc->name, proc->state); //apagar
  swapProc(RUNNABLE, proc);
  //Colocar este processo no final da fila dos processos prontos.
  cprintf("\n yield DEPOIS nr:%d, %s, %d", proc->pid, proc->name, proc->state); //apagar
  sched();
  release(&ptable.lock);
  //cprintf("\nyield depois nr:%d, %s, %d", proc->pid, proc->name, proc->state); //apagar
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot 
    // be run from main().
    first = 0;
    iinit(ROOTDEV);
    initlog(ROOTDEV);
  }
  
  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  if(proc == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }

  // Go to sleep.
  proc->chan = chan;
  proc->state = SLEEPING;
	cprintf("\n sleep ANTES nr:%d, %s, %d", proc->pid, proc->name, proc->state); //apagar
	//teste(2);//apagar
	swapProc(SLEEPING, proc);
	cprintf("\n sleep DEPOIS nr:%d, %s, %d", proc->pid, proc->name, proc->state); //apagar
  //Tirar este da primeira posição de pronto e colocar na ultima posição dos bloqueados e reorganizar o vetor.
  sched();

  // Tidy up.
  proc->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;
  //cprintf("\nwakeup1 inicio nr:"); //apagar	
  for(p = ptable.procBloq; p < &ptable.procBloq[NPROC]; p++){
    if(p->state == SLEEPING && p->chan == chan){
      p->state = RUNNABLE;
      //teste(3);//apagar
      swapProc(RUNNABLE, p);
      //colocar este processo para a ultima posição do vetor de prontos.
    }
  }

   //cprintf("\nwakeup1 fim nr:"); //apagar
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;
cprintf("\nkill desbloqueado nr:"); //apagar	
  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
	  //cprintf("\nkill desbloqueado nr:%d, %s, %d", p->pid, p->name, p->state); //apagar	
      p->killed = 1;
      release(&ptable.lock);
      return 0;
    }
  }
  /*
  for(p = ptable.procBloq; p < &ptable.procBloq[NPROC]; p++){
    if(p->pid == pid){
		//cprintf("\nkill bloqueado nr:%d, %s, %d", p->pid, p->name, p->state); //apagar	
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  */
  release(&ptable.lock);
  return -1;
}

//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  int i;
  struct proc *p;
  char *state;
  uint pc[10];
  
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
    cprintf("%d %s %s", p->pid, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
}
