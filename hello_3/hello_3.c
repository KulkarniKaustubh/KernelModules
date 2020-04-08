#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int hello_3_data = 3;

static int __init hello_3 (void)
{
  printk (KERN_ALERT "Hello word %d\n", hello_3_data);
  return 0;
}

static void __exit hello_3_exit (void)
{
  printk (KERN_ALERT "Gbye world %d\n", hello_3_data);
}

module_init (hello_3);
module_exit (hello_3_exit);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("KMK");
MODULE_DESCRIPTION ("Printing hello world differently");
