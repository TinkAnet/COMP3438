#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DRIVER_NAME "echo_driver"
#define N_D 1
#define S_N 1

static dev_t devno;
static struct cdev form;

static int echo_write(struct file *fp, const char __user *buf, size_t len, loff_t *offset) {
    char output[256];
    if (len > 256 || copy_from_user(output, buf, len))
	return -1;

    output[len] = '\0';
    printk("Received from user: %s\n", output);
    return len;
}

static struct file_operations fops = {
    owner : THIS_MODULE,
    write : echo_write,
};

static int __init echo_init(void) {
    int ret;
    ret = alloc_chrdev_region(&devno, S_N, N_D, DRIVER_NAME);
    if (ret < 0) {
        printk("Failed to allocate device number.\n");
        return ret;
    }
    cdev_init(&form, &fops);
    form.owner = THIS_MODULE;
    ret = cdev_add(&form, devno, N_D);
    if (ret < 0) {
        printk("Failed to add character device.\n");
        return ret;
    }
    return 0;
}

static void __exit echo_exit(void) {
    cdev_del(&form);
    unregister_chrdev_region(devno, N_D);
    printk("Echo driver unloaded.\n");
}

module_init(echo_init);
module_exit(echo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jason");
MODULE_DESCRIPTION("Character device driver for echoing user input.");
