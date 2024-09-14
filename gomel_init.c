#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>

#define DRVNAME "gomel"
#define DEV_MAJOR 508
extern struct file_operations fops;

static dev_t         gomel_dev_num;
static struct class *gomel_dev_class;
static struct cdev   gomel_dev;

static int __init gomel_init(void) {
	// if( alloc_chrdev_region(&gomel_dev_num, 1, 5, DRVNAME) < 0) {
	// 	printk("%s: failed to allocate device number\n", DRVNAME);
	// 	return -1;
	// }
	gomel_dev_num = MKDEV(DEV_MAJOR, 1);
	gomel_dev_class = class_create(DRVNAME);
	if (IS_ERR(gomel_dev_class)) {
		printk(KERN_ALERT "%s: failed to create device class\n", DRVNAME);
		goto err_class;
	}
	
	if(device_create(gomel_dev_class, NULL, gomel_dev_num, NULL, DRVNAME) == NULL) {
		printk("%s: failed to create device file\n", DRVNAME);
		goto err_file;
	}

	cdev_init(&gomel_dev, &fops);

	if(cdev_add(&gomel_dev, gomel_dev_num, 1) == -1) {
		printk("%s: failed to add device to kernel\n", DRVNAME);
		goto err_add;
	}

	printk(KERN_NOTICE "%s: char dev %d %d registered\n", DRVNAME, gomel_dev_num>>20, gomel_dev_num&0xfffff);
	return 0;
err_add:   device_destroy(gomel_dev_class, gomel_dev_num);
err_file:  class_destroy(gomel_dev_class);
err_class: unregister_chrdev_region(gomel_dev_num, 1);
	return -1;
}

static void __exit gomel_exit(void) {
	cdev_del(&gomel_dev);
	device_destroy(gomel_dev_class, gomel_dev_num);
	class_destroy(gomel_dev_class);
	unregister_chrdev(DEV_MAJOR, DRVNAME); 
	printk("%s: char dev %d %d finished\n", DRVNAME, gomel_dev_num>>20, gomel_dev_num&0xfffff);
}

module_init(gomel_init);
module_exit(gomel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kirill Shileev");
MODULE_DESCRIPTION("Mill machine controller");
