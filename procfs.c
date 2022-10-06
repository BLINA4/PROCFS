#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#define BUFSIZE         1024
#define FILENAME_LENGTH 768
#define PERMISSIONS     0666

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BLIN4IK97");

static int timer = 5;
module_param(timer, int, S_IRUGO);

static char *filename;
module_param(filename, charp, S_IRUGO);

static struct proc_dir_entry *ent;

static ssize_t mywrite( struct file *file, const char __user *ubuf, size_t count, loff_t *ppos ) 
{
  int num, c, i;
  char buf[BUFSIZE];

  if (*ppos > 0 || count > BUFSIZE)
	return -EFAULT;
  
  if (copy_from_user(buf, ubuf, count))
	return -EFAULT;
  
  num = sscanf(buf, "%d %s", &i, filename);

  if (num != 2)
	return -EFAULT;
	
  timer = i; 
  c = strlen(buf);
  *ppos = c;
  
  return c;
}

static ssize_t myread( struct file *file, char __user *ubuf, size_t count, loff_t *ppos ) 
{
  char buf[BUFSIZE];
  int len = 0;

  if (*ppos > 0 || count < BUFSIZE)
	return 0;

  len += sprintf(buf, "timer = %d\n", timer);
  len += sprintf(buf + len, "filename = %s\n", filename);
	
  if (copy_to_user(ubuf, buf, len))
	return -EFAULT;
  *ppos = len;
  
  return len;
}

struct proc_ops myops =
{
  .proc_read = myread,
  .proc_write = mywrite
};

static int procfs_init( void )
{
  filename = kmalloc(FILENAME_LENGTH * sizeof(char), GFP_KERNEL);
  ent = proc_create("mydev", PERMISSIONS, NULL, &myops); 
  //printk(KERN_INFO "hello...\n");

  return 0;
}

static void procfs_cleanup( void )
{
  proc_remove(ent);
  kfree(filename);
  //printk(KERN_INFO "bye ...\n");
}

module_init(procfs_init);
module_exit(procfs_cleanup);

