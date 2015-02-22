#include <linux/module.h>

int init_module(void) {
	printk(KERN_INFO "tester 1: Module loaded successfully\n");
	return 0;
}

void cleanup_module(void) {
	printk(KERN_INFO "tester 1: Module unloaded successfully\n");
}
