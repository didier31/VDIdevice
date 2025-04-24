#include <sys/param.h>
#include <sys/conf.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/systm.h>
#include <sys/ioccom.h>

#include "src/include/vdmc.h"
#include "src/krn/include/kthreadsafe_queue.h"

#include <sys/proc.h>

static int vdmc_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
                     struct thread *td) {
  int error = 0;
  uprintf("%s()\n", __func__);
  switch (cmd) {
  case IOCTL_NEW_VS_DEVICE:
    uprintf("NEW_VS_DEVICE_CMD\n");
    break;
  case IOCTL_DELETE_VS_DEVICE:
    uprintf("DELETE_VS_DEVICE_CMD\n");
    break;
  case IOCTL_LIST_VS_DEVICES:
    uprintf("LIST_VS_DEVICES_CMD\n");
    break;
  case IOCTL_KRN_REQUEST:
    uprintf("IOCTL_KRN_REQUEST_CMD\n");
    break;  
  default:
    error = ENOTTY;
    break;
  }
  return (error);
}

static int vdmc_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
  uprintf("%s()\n", __func__);
  return 0;
}
static int vdmc_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
  uprintf("%s()\n", __func__);
  return 0;
}

static int vdmc_write(struct cdev *dev, struct uio *uio, int ioflag)
{
  uprintf("%s()\n", __func__);
  return 0;
}

static int vdmc_read(struct cdev *dev, struct uio *uio, int ioflag)
{
  uprintf("%s()\n", __func__);
  return 0;
}

static struct cdevsw vdmc_cdevsw = {
  .d_version = D_VERSION, .d_name = "vdmc", .d_open = vdmc_open, .d_close = vdmc_close, .d_read = vdmc_read, .d_write = vdmc_write,
  .d_ioctl = vdmc_ioctl};

static int vdmc_modevent(module_t mod __unused, int event, void *arg __unused) {
  int error = 0;
  static struct cdev* vdmc_dev;
  switch (event) {
  case MOD_LOAD:
    uprintf("Hello, world!\n");
    vdmc_dev = make_dev(&vdmc_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600, "vdctl");
    break;
  case MOD_UNLOAD:
    destroy_dev(vdmc_dev);
    uprintf("Good-bye, cruel world!\n");
    break;
  default:
    error = EOPNOTSUPP;
    break;
  }
  return (error);
}

static moduledata_t vdmc_mod = {"vdmc", vdmc_modevent, NULL};
DECLARE_MODULE(mod, vdmc_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
