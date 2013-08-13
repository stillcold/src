#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void){
    printk(KERN_ALERT "This is Kernel speaking, Hello, user space!\n");
    return 0;
}

static void hello_exit(void){
    printk(KERN_ALERT "Kernel says, Goodbye and see you!\n");
}

module_init(hello_init);
module_exit(hello_exit);
