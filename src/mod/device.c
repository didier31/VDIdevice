#include <sys/param.h>
#include <sys/conf.h>
#include <sys/systm.h>

#include "src/include/device.h"


static int device_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
  uprintf("%s()\n", __func__);
  return 0;
}
static int device_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
  uprintf("%s()\n", __func__);
  return 0;
}
static int device_write(struct cdev *dev, struct uio *uio, int ioflag)
{
  uprintf("%s()\n", __func__);
  return 0;
}

static int device_read(struct cdev *dev, struct uio *uio, int ioflag)
{
  uprintf("%s()\n", __func__);
  return 0;
}

static struct cdevsw dev_cdevsw = {
    .d_version = D_VERSION, .d_open = device_open, .d_close = device_close, .d_read = device_read, .d_write = device_write,
    .d_name = "vd%d"};


struct cdev* make_media_a_device(char* virtualMediaPathName)
{
    static int deviceOrdinal = 0;
    struct cdev* cr = make_dev(&dev_cdevsw, deviceOrdinal, UID_ROOT, GID_WHEEL, 0600, "vd");
    if (cr)
    {
        deviceOrdinal++;
    }
    return cr;
}

void unmake_media_a_device(struct cdev* dev)
{
    destroy_dev(dev);
}