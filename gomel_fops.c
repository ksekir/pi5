#include <linux/module.h>
#include <linux/fs.h>

extern const char* gomel_name;
enum { 
    FREE = 0, 
    USED = 1, 
}; 
 
/* Is device open? Used to prevent multiple access to device */ 
static atomic_t already_open = ATOMIC_INIT(FREE); 
 
static char ks_buf[256];
static int ks_buf_count;  // how many bytes currently stored

static ssize_t gomel_read(struct file *file, char *us_buf, size_t count, loff_t *offs) {
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

static int gomel_open(struct inode *inode, struct file *file) {
	if (atomic_cmpxchg(&already_open, FREE, USED)) 
        return -EBUSY; 
    try_module_get(THIS_MODULE);
	printk("%s: open\n", gomel_name);
	return 0;
}

static int gomel_close(struct inode *inode, struct file *file) {
	atomic_set(&already_open, FREE);
    module_put(THIS_MODULE); 
	printk("%s: close\n", gomel_name);
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
