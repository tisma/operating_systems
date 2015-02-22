#include <linux/module.h>

int init_tester_2(void) {
	printk(KERN_INFO "tester_2: Module loaded successfully\n");
	return 0;
}

void unload_tester_2(void) {
	printk(KERN_INFO "tester_2: Module unloaded successfully\n");
}

module_init(init_tester_2);
module_exit(unload_tester_2);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("tisma@linux.com");
MODULE_DESCRIPTION("This module is a demonstration of two things: \n\ \
\t\tfirst, that init_module and cleanup_module can be renamed, and \n \
\t\tsecond, that there exist macros that are used to annotate the\n \
\t\tmodule code. \n \
\t\tThese annotations may be shown by using modinfo");

MODULE_SUPPORTED_DEVICE("tty");
MODULE_ALIAS("ok");
MODULE_VERSION("0.0.1");
