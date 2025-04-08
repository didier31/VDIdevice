#include <sys/param.h>
#include <sys/conf.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/systm.h>

#include <sys/ioccom.h>
#include "src/include/mod.h"

static struct cdevsw mod_cdevsw;
static struct cdev* mod_dev;

static int mod_modevent(module_t mod __unused, int event, void *arg __unused) {
  int error = 0;
  switch (event) {
  case MOD_LOAD:
    uprintf("Hello, world!\n");
    mod_dev = make_dev(&mod_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600, "mod");
    break;
  case MOD_UNLOAD:
    destroy_dev(mod_dev);
    uprintf("Good-bye, cruel world!\n");
    break;
  default:
    error = EOPNOTSUPP;
    break;
  }
  return (error);
}

static int mod_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
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
  default:
    error = ENOTTY;
    break;
  }
  return (error);
}

static int mod_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
  uprintf("%s()\n", __func__);
  return 0;
}
static int mod_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
  uprintf("%s()\n", __func__);
  return 0;
}
static int mod_write(struct cdev *dev, struct uio *uio, int ioflag)
{
  uprintf("%s()\n", __func__);
  return 0;
}

static int mod_read(struct cdev *dev, struct uio *uio, int ioflag)
{
  uprintf("%s()\n", __func__);
  return 0;
}

static struct cdevsw mod_cdevsw = {
    .d_version = D_VERSION, .d_open = mod_open, .d_close = mod_close, .d_read = mod_read, .d_write = mod_write,
    .d_ioctl = mod_ioctl, .d_name = "mod"};

static moduledata_t mod_mod = {"mod", mod_modevent, NULL};
DECLARE_MODULE(mod, mod_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
