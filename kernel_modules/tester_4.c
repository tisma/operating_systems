#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 256

struct proc_dir_entry *proc_entry, *root_dir = NULL;
char result_buffer[BUFFER_SIZE];
char before[BUFFER_SIZE];
int count;
int temp = 1;

ssize_t write(struct file* f, const char __user* buf, size_t len, loff_t* off) {
	printk(KERN_INFO "tester_4: somebody wrote to this file\n");
	if (copy_from_user(result_buffer, buf, len))
		return -EFAULT;
	return len;
}

ssize_t read(struct file* f, char __user* buf, size_t c, loff_t* off) {
	int len = 0;
	if (temp == 0) {
		temp = 1;
		return 0;
	}

	sprintf(before, "[%s] ", result_buffer);
	if (count <= 1)
		sprintf(result_buffer, "tester_4 read %d\n", count++);
	else
		sprintf(result_buffer, "tester_4 read again!! count = %d\n", count++);

	len = strlen(result_buffer);
	if (copy_to_user(buf, result_buffer, len))
		return -EFAULT;

	printk(KERN_ERR "tester_4: page before = [%s]\n\tpage after = [%s]\n",
		before, result_buffer);
	
	temp = 0;
	
	return len;
}

static const struct file_operations file_ops = {
	.owner = THIS_MODULE,
	.read = read,
	.write = write,
};

int init_tester_4(void) {
	count = 1;

	proc_entry = proc_create("tester_4", 438, NULL, &file_ops);

	strcpy(result_buffer, "initialized\n");

	if (proc_entry == NULL) {
		printk(KERN_ERR "tester_4: Couldn't create proc entry\n");
		return -ENOMEM;
	}

	printk(KERN_INFO "tester_4: Module loaded successfully\n");

	return 0;
}

void unload_tester_4(void) {
	remove_proc_entry("tester_4", root_dir);
	printk(KERN_INFO "tester_4: Module unloaded successfully\n");
}

module_init(init_tester_4);
module_exit(unload_tester_4);

MODULE_LICENSE("GPL");
