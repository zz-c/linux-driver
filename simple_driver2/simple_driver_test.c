#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define DEVICE_PATH "/dev/simple_driver"

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd == -1) {
        perror("Failed to open the device");
        return 1;
    }

    // Write data to the device
    const char *message = "Hello from user space!";
    ssize_t bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) {
        perror("Failed to write to the device");
        close(fd);
        return 1;
    }

    printf("Written %ld bytes to the device\n", bytes_written);

    // Read data from the device
    char buffer[256];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Failed to read from the device");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';  // Null terminate the string
    printf("Read %ld bytes from the device: %s\n", bytes_read, buffer);

    close(fd);
    return 0;
}
