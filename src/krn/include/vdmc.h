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

#ifdef __cplusplus
extern "C" 
{
#endif
    extern struct cdevsw vdmc_cdevsw; 
#ifdef __cplusplus    
}
#endif

#endif