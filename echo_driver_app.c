#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    char input[256];
    int len;

    fd = open("/dev/comp3438helloworld_dev_file", O_WRONLY);
    if (fd == -1) {
        printf("Failed to open device file");
        return;
    }

    printf("Enter a string to echo: ");
    fgets(input, sizeof(input), stdin);
    len = strlen(input);

    if (write(fd, input, len) < 0) {
        printf("Failed to write to device file");
    }
    close(fd);
    return;
}
