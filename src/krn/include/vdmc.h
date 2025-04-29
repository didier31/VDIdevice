#ifndef __KRN_VDMC_H__
#define __KRN_VDMC_H__

#ifdef __cplusplus
#define  EXTERN_C extern "C"
#else
#define  EXTERN_C
#endif

EXTERN_C int vdmc_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
    struct thread *td);

EXTERN_C int vdmc_open(struct cdev *dev, int oflags, int devtype, struct thread *td);

EXTERN_C int vdmc_close(struct cdev *dev, int fflag, int devtype, struct thread *td);

EXTERN_C int vdmc_write(struct cdev *dev, struct uio *uio, int ioflag);

EXTERN_C int vdmc_read(struct cdev *dev, struct uio *uio, int ioflag);

EXTERN_C struct cdevsw vdmc_cdevsw = {
    .d_version = D_VERSION, .d_name = "vdmc", .d_open = vdmc_open, .d_close = vdmc_close, .d_read = vdmc_read, .d_write = vdmc_write,
    .d_ioctl = vdmc_ioctl};

#endif