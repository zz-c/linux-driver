#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>  // for copy_to_user and copy_from_user

#define DEVICE_NAME "simple_driver"
#define MAJOR_NUM 100

static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *buffer, size_t len, loff_t *offset);
static ssize_t device_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset);

//static int major_num;
static char message[256] = {0};  // This is the message that will be read/written
static int message_size = 0;

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
};

// Open the device
static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "simple_driver: Device opened\n");
    return 0;
}

// Release the device
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "simple_driver: Device closed\n");
    return 0;
}

// Read from the device
static ssize_t device_read(struct file *file, char __user *buffer, size_t len, loff_t *offset) {
    int ret = 0;
    if (*offset >= message_size) {
        return 0;  // End of message
    }

    if (*offset + len > message_size) {
        len = message_size - *offset;  // Read only the remaining data
    }

    ret = copy_to_user(buffer, message + *offset, len);
    if (ret == 0) {
        *offset += len;
        printk(KERN_INFO "simple_driver: Sent %zu characters to the user\n", len);
        return len;
    } else {
        printk(KERN_ERR "simple_driver: Failed to send %d characters to the user\n", ret);
        return -EFAULT;
    }
}

// Write to the device
static ssize_t device_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
    int ret = 0;
    if (len > 255) {
        len = 255;  // Ensure we don't overflow the buffer
    }

    ret = copy_from_user(message, buffer, len);
    if (ret == 0) {
        message_size = len;
        printk(KERN_INFO "simple_driver: Received %zu characters from the user\n", len);
        return len;
    } else {
        printk(KERN_ERR "simple_driver: Failed to receive %d characters from the user\n", ret);
        return -EFAULT;
    }
}

// Initialize the driver
static int __init simple_driver_init(void) {
    int result;

    // Register the character device
    result = register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
    if (result < 0) {
        printk(KERN_ALERT "simple_driver: Failed to register device with %d\n", result);
        return result;
    }

    printk(KERN_INFO "simple_driver: Device registered with major number %d\n", MAJOR_NUM);
    return 0;
}

// Cleanup the driver
static void __exit simple_driver_exit(void) {
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
    printk(KERN_INFO "simple_driver: Device unregistered\n");
}

module_init(simple_driver_init);
module_exit(simple_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZZ");
MODULE_DESCRIPTION("A simple Linux driver");
