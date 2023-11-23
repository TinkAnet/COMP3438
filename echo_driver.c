#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <asm/uaccess.h>

#define DRIVER_NAME "echo_driver"
#define N_D 10
#define S_N 1

static dev_t devno;
static int major;
static struct cdev form;


static int write(struct file * fp, const char __user *buf, size_t len, loff_t * offset) {
    int ret = 0;
    char buffer[256];
    ret = copy_from_user(buffer, buf, len);
    if (ret) {
        printk("Fail to copy data from the kernel space to the user space.\n");
        return ret;
    }
    if(len >= 256 || len <=0 )return -1; 
    
    buffer[len] = '\0';
    printk("Received from user : %s",buffer);
    return len;
}

static int open_impl(struct inode *pinode, struct file *pf){
    printk("Device " DRIVER_NAME " open.\n");
    return 0;
}

static int release_impl(struct inode *pinode, struct file *pf) {
    printk("Device " DRIVER_NAME " release.\n");
    return 0;
}

static struct file_operations fops = {
    owner: THIS_MODULE,
    write: write,
    release: release_impl,
};

static int __init helloworld_init(void) {
    int ret;
    ret = alloc_chrdev_region(&devno, S_N, N_D, DRIVER_NAME);
    if (ret < 0) {
        printk("Device " DRIVER_NAME " cannot get major number.\n");
        return ret;
    }
    major = MAJOR(devno);
    printk("Device " DRIVER_NAME " initialized (Major number = %d).\n", major);


    cdev_init(&form, &fops);
    form.owner = THIS_MODULE;
    ret = cdev_add(&form, devno, N_D);
    if (ret < 0) {
        printk("Device " DRIVER_NAME " register fail.\n");
        return ret;
    }
    return 0;
}

static void __exit helloworld_exit(void) {
    cdev_del(&form);
    unregister_chrdev_region(devno, N_D);
    printk("Device " DRIVER_NAME " unloaded.\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Letao Zhao");
MODULE_DESCRIPTION("Char device driver for helloworld!");
