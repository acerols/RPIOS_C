#include "sched.h"
#include "irq.h"
#include "printf.h"

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);
struct task_struct * task[NR_TASKS] = {&(init_task), };
uint64_t nr_tasks = 0;
uint64_t Now_task = 0;

struct cpu_context context_temp[1];

void preempt_disable(void)
{
	current->preempt_count++;
}

void preempt_enable(void)
{
	current->preempt_count--;
}

uint64_t get_task_num()
{
	return nr_tasks;
}

void _schedule(void)
{
	preempt_disable();
	int next,c;
	struct task_struct * p;
	while (1) {
		c = -1;
		next = 0;
		for (int i = 0; i < NR_TASKS; i++){
			p = task[i];
			if (p && p->state == TASK_RUNNING && p->counter > c) {
				c = p->counter;
				next = i;
			}
		}
		if (c) {
			break;
		}
		for (int i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
	switch_to(task[next]);
	preempt_enable();
}

void sched()
{
	struct task_struct *prev = task[Now_task];
	if(nr_tasks == 1){
		prev = task[0];
		struct task_strcut *next = task[0];
		cpu_switch_to(prev, next);
	}
	if(Now_task < (nr_tasks -1)){
		Now_task++;
	}
	else{
		Now_task = 0;
	}
	struct task_struct *next = task[Now_task];
	printf("No : %d\nTask : %d\n", Now_task, nr_tasks);
	cpu_switch_to(prev, next);
	return;
}

void switch_to(struct task_struct *next) 
{
	if (current == next) 
		return;
	struct task_struct * prev = current;
	current = next;
	printf("Context Switch!!! Next process : %10x\n", next);
	cpu_switch_to(prev, next);
}

void schedule_tail(void) {
	preempt_enable();
}


void timer_tick()
{
	--current->counter;
	if (current->counter>0 || current->preempt_count >0) {
		return;
	}
	current->counter=0;
	//enable_irq();
	_schedule();
	disable_irq();
}

