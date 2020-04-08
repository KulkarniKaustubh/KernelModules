#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
    pr_info ("Hello world!\n");
    return 0;
}

static void hello_exit(void)
{
    pr_info ("Goodbye world!\n");
}
module_init(hello_init);
module_exit(hello_exit);
