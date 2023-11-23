#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main() {
    int fd;
    int count;
    char buf[256];
    fd = open("/dev/echo_driver", O_WRONLY);
    if (fd == -1) {
        printf("Fail to open device file.\n");
        return;
    }
    printf("String to echo: ");
    fget(buf,sizeof(buf),stdin);
    write(fd, buf, 256);
    close(fd);
}

