#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init hello_2 (void)
{
  printk (KERN_ALERT "Hello world 2\n");
  return 0;
}

static void __exit hello_2_exit (void)
{
  printk (KERN_ALERT "Gbye world 2\n");
}

module_init (hello_2)
module_exit (hello_2_exit);
