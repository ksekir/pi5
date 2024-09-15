#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

 
static char ks_buf[256];
static int ks_buf_count;  // how many bytes currently stored

static ssize_t gomel_read(struct file *fp, char *us_buf, size_t count, loff_t *offs) {
	int n_copy = umin(count, ks_buf_count);  // no reason to read more then currntly stored in ks buffer

	int n_uncopied = copy_to_user(us_buf, ks_buf,  n_copy);
	return n_copy - n_uncopied;
}

static ssize_t gomel_write(struct file *fp, const char *us_buf, size_t count, loff_t *offs) {
	int n_copy = umin(count, sizeof(ks_buf));  // no way to write more the ks buffer can accomodate

	int n_uncopied = copy_from_user(ks_buf, us_buf, n_copy);
	ks_buf_count = n_copy;
	return n_copy - n_uncopied;
}

const struct proc_ops proc_ops = { 
    .proc_read = gomel_read, 
    .proc_write = gomel_write
}; 

MODULE_LICENSE("GPL");
