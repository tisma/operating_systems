#include <linux/module.h>

int param1 = 3;
module_param(param1, int, S_IRUGO);
char* param2 = "Hello World";
module_param(param2, charp, S_IRUGO);
int param3[5] = { 1, 2, 3, 4, 5 };
int param_cnt = 5;
module_param(param_cnt, int, S_IRUSR);
module_param_array(param3, int, &param_cnt, S_IRUGO);

int init_tester_3(void) {
	int i;
	printk(KERN_INFO "tester_3: Module loaded successfully\n");
	printk(KERN_INFO "param1 = %d\n", param1);
	printk(KERN_INFO "param2 = %s\n", param2);
	for (i = 0; i < param_cnt; i++) {
		printk(KERN_INFO "param3[%d] = %d ", i, param3[i]);
	}
	printk(KERN_INFO "\n");
	return 0;
}

void unload_tester_3(void) {
	printk(KERN_INFO "tester_3: Module unloaded successfully\n");
}

module_init(init_tester_3);
module_exit(unload_tester_3);
MODULE_LICENSE("GPL");
