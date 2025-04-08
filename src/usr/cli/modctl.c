#include "../include/mod.h"
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

char titi[] = "toto";

int main(int argc, char **argv) {
  int fd = open("/dev/mod", O_RDWR);
  int i;
  if (fd < 0)
    err(1, "open(/dev/mod)");
  i = ioctl(fd, IOCTL_NEW_VS_DEVICE, titi);
  if (i < 0)
    err(1, "ioctl(/dev/mod)");
  close(fd);
  return 0;
}