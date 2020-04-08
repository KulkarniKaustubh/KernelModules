#include <linux/init.h>
#include <linux/fs.h>    /* for struct file* filp , struct inode * */
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>  /* for put_user */
#include "cdev.h"

#define SUCCESS 0
#define DEVICE_NAME "kaustubh"
#define OWNER_NAME "kaustubh"
#define BUF_LEN 10000
#define KI KERN_INFO

static int Major;   // To get major number of the device driver
static int Device_open = 0; // To keep count of number of times device has been opened

static char msg[BUF_LEN]; // msg given by our device
static char *msg_ptr;

static char str[30];
static char *str_ptr;

static struct file_operations fops = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release,
};

// Function to load module

int load_register_device (void)
{
  Major = register_chrdev(0, DEVICE_NAME, &fops);

  if (Major < 0) {
    printk (KI "Error registering device with major number %d\n", Major);
    return Major;
  }

  printk (KI "Major number assigned is: %d\n", Major);
  printk (KI "Create driver with\n");
  printk (KI "mknod /dev/%s c %d 0\n", DEVICE_NAME, Major);
  printk(KI "Try various minor numbers. Try to cat and echo to\n");
  printk(KI "the device file.\n");
  printk(KI "Remove the device file and module when done.\n");

  return SUCCESS;
}

void unload_cleanup_module (void)
{
  // int ret = __unregister_chrdev (Major, DEVICE_NAME);
  unregister_chrdev (Major, DEVICE_NAME);
  #if 0
  if (ret < 0) {
    printk (KI "Failure in unregister_chrdev: %d\n", ret);
  }
  #endif
  printk (KI "Unloaded.\n");
}

static int device_open (struct inode *inode, struct file *file)
{
  static int counter = 0;

  if (Device_open)
    return -EBUSY;

  Device_open++;
  sprintf (msg, "Opened %d times in the past.\n", counter++);
  msg_ptr = msg;
  /* use cat /proc/modules/ to see 3rd column which shows how many
   * processes are using the module
   * try_module_get adds a number to that and module_put subtracts one from it
   */
  try_module_get (THIS_MODULE);

  return SUCCESS;
}

static int device_release (struct inode* inode, struct file *file)
{
  Device_open--;

  module_put (THIS_MODULE);  // subtracting one from number of processes otherwise it will never unload

  return 0;
}

static ssize_t device_read (struct file *filp,       // inside include fs.h
                            char* buffer,            // buffer to fill with data
                            size_t length,           // length of the buffer
                            loff_t *offset)
{
  int bytes_read = 0; // number of bytes read by the buffer


  if (*msg_ptr == 0)    // end of message
    return 0;

  char nl[2] = "\n";
  char *nl_ptr;
  nl_ptr = nl;

  while (length && *msg_ptr) {
    put_user (*(msg_ptr++), buffer++);
    #if 0
    length--;
    put_user (*nl, buffer++);
    length--;
    put_user (str_ptr, buffer++);
    #endif

    length--;
    bytes_read++;
  }
  sprintf (str, "Bytes read: %d.\n", bytes_read);
  str_ptr = str;
  printk (KI "BR: %d\n", bytes_read);

  return bytes_read;
}

static ssize_t device_write (struct file *filp, const char *buff, size_t len, loff_t *off)
{
  printk (KI "Write not supported.\n");
  return -EINVAL;
}

module_init (load_register_device);
module_exit (unload_cleanup_module);
