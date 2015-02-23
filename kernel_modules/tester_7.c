#include <linux/module.h>
#include <linux/workqueue.h>

struct workqueue_struct* queue;
struct delayed_work dwork;
int count = 0;

void function(struct work_struct* work) {
	printk(KERN_INFO "count: %d\n", count++);
	queue_delayed_work(queue, &dwork, HZ);
}

int init_module() {
	queue = create_workqueue("queue");
	INIT_DELAYED_WORK(&dwork, function);
	queue_delayed_work(queue, &dwork, HZ);
	return 0;
}

void cleanup_module(void) {
	flush_workqueue(queue);
	if (delayed_work_pending(&dwork)) {
		cancel_delayed_work(&dwork);
		flush_workqueue(queue);
	}
	destroy_workqueue(queue);
	printk(KERN_INFO "Module removed\n");
}

MODULE_LICENSE("GPL");
