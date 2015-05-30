#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <asm/i387.h>

#define LOOPS 1000000

int list[LOOPS];
int idx = 0, cs1 = 0, cs2 = 0;
struct task_struct *t1, *t2;
struct semaphore lock;
struct timeval tm1, tm2;

int consumer(void* ptr)
{
	printk(KERN_INFO "Consumer TID %d\n", (int)ptr);

	do_gettimeofday(&tm1);
	while (1) {
		if (!down_interruptible(&lock)) {
			if (idx >= LOOPS) {
				up(&lock);
				break;
			}
		}
		list[idx++] += 1;
		up(&lock);
		if ((int)ptr == 1)
			cs1++;
		else
			cs2++;
	}
	do_gettimeofday(&tm2);
	printk(KERN_INFO "Consumer %d done\n", (int)ptr);
	return 0;
}

int semaphore_init(void)
{
	int i, id1 = 1, id2 = 2, lo_cnt = 0, hi_cnt = 0;
	for (i = 0; i < LOOPS; i++)
		list[i] = 0;

	sema_init(&lock, 1);

	t1 = kthread_run(consumer, (void*)id1, "cons1");
	t2 = kthread_run(consumer, (void*)id2, "cons2");

	msleep(5000);

	for (i = 0; i < LOOPS; i++) {
		if (list[i] == 0) {
			lo_cnt++;
			printk(KERN_INFO "lo:%d ", i);
		} else if (list[i] > 1) {
			hi_cnt++;
			printk(KERN_INFO "hi:%d ", i);
		}
	}

	printk(KERN_INFO "lo_cnt=%d hi_cnt=%d cs1=%d cs2=%d total=%d\n",
			lo_cnt, hi_cnt, cs1, cs2, cs1 + cs2);
	printk(KERN_INFO "list[LOOPS]=%d\n", list[LOOPS]);
	return 0;
}

void semaphore_cleanup(void)
{
	printk(KERN_INFO "Inside cleanup_module\n");
	printk("Time: %d sec %d usec\n",
			(int)(tm2.tv_sec - tm1.tv_sec), (int)(tm2.tv_usec - tm1.tv_usec));
}

MODULE_LICENSE("GPL");
module_init(semaphore_init);
module_exit(semaphore_cleanup);

