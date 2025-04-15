#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../../include/vdmc.h"

char titi[] = "toto";

int main(int argc, char **argv) {
  int fd = open("/dev/vdctl", O_RDWR);
  int i;
  if (fd < 0)
    err(1, "open(/dev/vdctl)");
  i = ioctl(fd, IOCTL_DELETE_VS_DEVICE, 3);
  if (i < 0)
    err(1, "ioctl(/dev/vdctl)");
  close(fd);
  return 0;
}
