extern "C"
{
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/malloc.h>
}
#include "src/krn/include/vdmc.h"
#include "src/krn/include/io_queue.h"

extern "C" int vdmc_modevent(module_t mod __unused, int event, void *arg __unused) {
    int error = 0;
    static struct cdev* vdmc_dev;
    switch (event) {
    case MOD_LOAD:
      uprintf("Hello, world!\n");
      vdmc_dev = make_dev(&vdmc_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600, "vdctl");
      {
      io_requests_t _io_requests;
      io_requests = (io_requests_t*) malloc(sizeof(io_requests_t), M_IO_QUEUE, M_WAITOK);
      //*io_requests = _io_requests;
      }
      break;
    case MOD_UNLOAD:
      destroy_dev(vdmc_dev);
      free(io_requests, M_IO_QUEUE);
      uprintf("Good-bye, cruel world!\n");
      break;
    default:
      error = EOPNOTSUPP;
      break;
    }
    return (error);
  }