#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list my_timer;
static int count;

void my_timer_callback(unsigned long data) {
	printk(KERN_INFO "my_timer_callback called\n");
	if (count++ < 10)
		mod_timer(&my_timer, jiffies + 2*HZ);
}

int init_module(void) {
	int ret;
	count = 1;

	printk(KERN_INFO "Timer module installing\n");

	setup_timer(&my_timer, my_timer_callback, 0);

	printk(KERN_INFO "Starting timer to fire in 1 sec\n");

	ret = mod_timer(&my_timer, jiffies + HZ);
	if (ret)
		printk(KERN_INFO "Error in mod_timer\n");
	printk(KERN_EMERG "Ending");
	return 0;
}

void cleanup_module(void) {
	int ret;

	ret = del_timer(&my_timer);
	if (ret)
		printk(KERN_INFO "The timer is a zombie\n");

	printk(KERN_INFO "Timer module uninstalling\n");

	return;
}
