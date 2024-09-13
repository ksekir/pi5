#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kirill Shileev");
MODULE_DESCRIPTION("Mill machine controller");

static int __init gomel_init(void) {
	printk("Gomel init\n");
	return 0;
}

static void __exit gomel_exit(void) {
	printk("Gomel exit\n");
}

module_init(gomel_init);
module_exit(gomel_exit);
