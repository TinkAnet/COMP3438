#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  int fd;
  int count;
  char buf[256];
  scanf("%[^\n]", buf);

  fd = open("/dev/helloworld", O_WRONLY);
  if (fd == -1){
    printf("Fail to open device helloworld.\n");
    exit(-1);
  }

  count = read(fd, buf, 99);
  buf[count] = '\0';
  printf("%d bytes are written from\n", count);
  printf("you input is: %s\n",  buf);

  close(fd);
  return 0;
}
  

