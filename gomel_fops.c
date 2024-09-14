#include <linux/module.h>
#include <linux/fs.h>

static char ks_buf[256];
static int ks_buf_count;  // how many bytes currently stored

static ssize_t gomel_read(struct file *File, char *us_buf, size_t count, loff_t *offs) {
	int n_copy = umin(count, ks_buf_count);  // no reason to read more then currntly stored in ks buffer

	int n_uncopied = copy_to_user(us_buf, ks_buf,  n_copy);
	return n_copy - n_uncopied;
}

static ssize_t gomel_write(struct file *File, const char *us_buf, size_t count, loff_t *offs) {
	int n_copy = umin(count, sizeof(ks_buf));  // no way to write more the ks buffer can accomodate

	int n_uncopied = copy_from_user(ks_buf, us_buf, n_copy);
	ks_buf_count = n_copy;
	return n_copy - n_uncopied;
}

static int gomel_open(struct inode *device_file, struct file *instance) {
    try_module_get(THIS_MODULE);
	printk(KERN_INFO "open\n");
	return 0;
}

static int gomel_close(struct inode *device_file, struct file *instance) {
    module_put(THIS_MODULE); 
	printk(KERN_INFO "close\n");
	return 0;
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = gomel_open,
	.release = gomel_close,
	.read = gomel_read,
	.write = gomel_write
};

MODULE_LICENSE("GPL");
