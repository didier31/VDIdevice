#include <sys/param.h>
#include <sys/conf.h>
#include <sys/systm.h>

#include "src/include/vd.h"

#define DEFINE_DECLARE_IO_QUEUE

#include "src/krn/include/io_queue.h"

static int vd_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
  uprintf("%s()\n", __func__);
  return 0;
}
static int vd_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
  uprintf("%s()\n", __func__);
  return 0;
}
static int vd_write(struct cdev *dev, struct uio *uio, int ioflag)
{
  uprintf("%s()\n", __func__);
  struct krn_request_t write_request = {
    .type = krn_request_t::WRITE_VD,
    .payload {
      .io_buffer = { 
        .size = 0, 
        .ptr = NULL 
      }
    }
  };
  char description[51];
  snprintf(description, 51, "tsleep(write_request.payload.io_buffer.ptr = %p)", write_request.payload.io_buffer.ptr);
  tsleep(write_request.payload.io_buffer.ptr, 0, description, 0);
  return 0;
}

static int vd_read(struct cdev *dev, struct uio *uio, int ioflag)
{
  uprintf("%s()\n", __func__);
  struct krn_request_t read_request = {
    .type = krn_request_t::READ_VD,
    .payload {
      .io_buffer = { 
        .size = 0, 
        .ptr = NULL 
      }
    }
  };
  char description[51];
  snprintf(description, 51, "tsleep(read_request.payload.io_buffer.ptr = %p)", read_request.payload.io_buffer.ptr);
  tsleep(read_request.payload.io_buffer.ptr, 0, description, 0);
  return 0;
}

static struct cdevsw dev_cdevsw = {
  .d_version = D_VERSION, .d_name = "vd%d", .d_open = vd_open, .d_close = vd_close, .d_read = vd_read, .d_write = vd_write,
    };


struct cdev* make_media_a_vd(char* virtualMediaPathName)
{
    static int vdOrdinal = 0;
    struct cdev* cr = make_dev(&dev_cdevsw, vdOrdinal, UID_ROOT, GID_WHEEL, 0600, "vd");
    if (cr)
    {
        vdOrdinal++;
    }
    return cr;
}

void unmake_media_a_vd(struct cdev* dev)
{
    destroy_dev(dev);
}