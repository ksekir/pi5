#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>


extern const struct proc_ops proc_ops;

static const char* gomel_name = "gomel";
static struct proc_dir_entry *proc_dev;

static int __init gomel_init(void) {
	proc_dev = proc_create(gomel_name, 0666, NULL, &proc_ops); 
    if (NULL == proc_dev) { 
        pr_alert("Error:Could not initialize /proc/%s\n", gomel_name); 
        return -ENOMEM; 
    } 
 
    pr_info("/proc/%s: created\n", gomel_name); 
    return 0;
}

static void __exit gomel_exit(void) {
	proc_remove(proc_dev); 
    pr_info("/proc/%s: removed\n", gomel_name); 
}

module_init(gomel_init);
module_exit(gomel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kirill Shileev");
MODULE_DESCRIPTION("Mill machine controller");
