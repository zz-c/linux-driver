#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "simple_driver"
#define MAJOR_NUM 100

static int simple_driver_init(void);
static void simple_driver_exit(void);

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Simple Driver: Opened device\n");
    return 0;
}

static int device_close(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Simple Driver: Closed device\n");
    return 0;
}

static ssize_t device_read(struct file *file, char *buffer, size_t len, loff_t *offset) {
    printk(KERN_INFO "Simple Driver: Reading from device\n");
    return 0;
}

static ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset) {
    printk(KERN_INFO "Simple Driver: Writing to device\n");
    return len;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_close,
    .read = device_read,
    .write = device_write,
};

static int simple_driver_init(void) {
    int result;

    printk(KERN_INFO "Simple Driver: Initializing module\n");

    // 注册字符设备驱动，将设备与一个主设备号绑定
    result = register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
    if (result < 0) {
        printk(KERN_ALERT "Simple Driver: Registering the device failed with %d\n", result);
        return result;
    }

    printk(KERN_INFO "Simple Driver: Device registered successfully with major number %d\n", MAJOR_NUM);
    return 0;
}

static void simple_driver_exit(void) {
    printk(KERN_INFO "Simple Driver: Exiting module\n");
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}

module_init(simple_driver_init);
module_exit(simple_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZZ");
MODULE_DESCRIPTION("A simple Linux driver");

