#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/stat.h>
#include <linux/moduleparam.h>

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("KMK");

static short int myshort = 1;
static int myint = 400;
static long int mylong = 9999;
static char* mystr = "Kaustubh Kulkarni";
static int myarr[2] = {30, 40};
static int arr_argc = 0;

/*
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits,
 * for exposing parameters in sysfs (if non-zero) at a later stage.
 */

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystr, charp, 0000);
MODULE_PARM_DESC(mystr, "A character string");

/*
 * module_param_array(name, type, num, perm);
 * The first param is the parameter's (in this case the array's) name
 * The second param is the data type of the elements of the array
 * The third argument is a pointer to the variable that will store the number
 * of elements of the array initialized by the user at module loading time
 * The fourth argument is the permission bits
 */

module_param_array (myarr, int, &arr_argc, 0000);
MODULE_PARM_DESC (myarr, "Array of integers");

static int __init cmd_args_init (void)
{
  int i;
  printk (KERN_INFO "my short integer is: %hd\n", myshort);
  printk (KERN_INFO "my integer is: %d\n", myint);
  printk (KERN_INFO "my long integer is: %ld\n", mylong);
  printk (KERN_INFO "my name is: %s\n", mystr);
  for (i=0; i < 2; ++i) {
    printk (KERN_INFO "myarr[%d] = %d\n", i, myarr[i]);
  }
  printk (KERN_INFO "Got %d arguments for my integer array.\n", arr_argc);
  return 0;
}

static void __exit cmd_args_exit (void)
{
  printk (KERN_INFO "Exiting\n");
}

module_init (cmd_args_init);
module_exit (cmd_args_exit);
