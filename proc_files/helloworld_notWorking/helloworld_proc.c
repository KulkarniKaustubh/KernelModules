#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define procfs_name "kaus_helloworld"

struct proc_dir_entry *my_proc_file;

ssize_t procfile_read (struct file *fp, char *buff, size_t buff_len, loff_t *offset)
{
	int ret = 0;
	int i = 0;
	pr_info ("IN READ FUNCTION\n");
	pr_info ("Buffer length is buff_len: %zu\n", buff_len);
	while ( i < 10) {
		pr_info ("%c", buff[i]);
		i += 1;
	}
	pr_info ("\n");
	/*pr_info ("procfile read %s\n", fp->f_path.dentry->d_name.name);
	ret = copy_to_user (buff, "Hello World!\n", sizeof("Hello World!\n"));
	pr_info ("After copy_to_user ret: %d\n", ret);
	ret = sizeof("Hello World!\n");
	pr_info ("Returning the final ret: %d\n", ret);
	return ret;*/
	
	if (buff_len == 0) {
	  pr_info ("procfile read %s\n", fp->f_path.dentry->d_name.name);
	  ret = copy_to_user (buff, "Hello World!\n", sizeof("Hello World!\n"));
	  ret = sizeof("Hello World!\n");
	  buff_len = 0;
	  pr_info ("Returning the final ret: %d\n", ret);
          pr_info ("Buffer length is buff_len: %zu\n", buff_len);
	}
	return ret;
}

static const struct proc_ops proc_fops = {
    .proc_read  = procfile_read,
};

static int __init startmodule(void)
{
    my_proc_file = proc_create(procfs_name, 0644, NULL, &proc_fops);
    if(!my_proc_file) {
	    proc_remove(my_proc_file);
	    pr_alert("Error:Could not initialize /proc/%s\n",procfs_name);
	    return -ENOMEM;
    }

    pr_info("/proc/%s created\n", procfs_name);
    return 0;
}

static void stopmodule(void)
{
    proc_remove(my_proc_file);
    pr_info("/proc/%s removed\n", procfs_name);
}

MODULE_LICENSE("GPL");

module_init (startmodule);
module_exit (stopmodule);
