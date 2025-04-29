#include "src/include/vdmc.h"

#include "src/krn/include/io_queue.h"

extern "C"
{
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/systm.h>
#include <sys/ioccom.h>
#include <sys/proc.h>
}

extern "C" int vdmc_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
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
    *((struct krn_request_t*) data) = io_requests.exit();
    return 0;

  case IOCTL_SRV_ANSWER:
    uprintf("IOCTL_KRN_REQUEST_CMD\n");
    wakeup(((struct krn_request_t*) data)->payload.io_buffer.ptr);
    return 0;

  default:
    error = ENOTTY;
    break;
  }
  return (error);
}

extern "C" int vdmc_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
  return -1;
}
extern "C" int vdmc_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
  return -1;
}

extern "C" int vdmc_write(struct cdev *dev, struct uio *uio, int ioflag)
{
  return -1;
}

extern "C" int vdmc_read(struct cdev *dev, struct uio *uio, int ioflag)
{
  return -1;
}

extern "C" struct cdevsw vdmc_cdevsw = {
  .d_version = D_VERSION, .d_name = "vdmc", .d_open = vdmc_open, .d_close = vdmc_close, .d_read = vdmc_read, .d_write = vdmc_write,
  .d_ioctl = vdmc_ioctl};

extern "C" int vdmc_modevent(module_t mod __unused, int event, void *arg __unused) {
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

extern "C" moduledata_t vdmc_mod = {"vdmc", vdmc_modevent, NULL};
extern "C"
{
  DECLARE_MODULE(mod, vdmc_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
}
