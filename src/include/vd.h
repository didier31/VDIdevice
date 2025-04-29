#ifndef __VDEVICE__
#define __VDEVICE__

extern "C" {
#include <sys/param.h>
#include <sys/conf.h>
}

extern "C" struct cdev *make_media_a_vd(char *virtualMediaPathName);

extern "C" void unmake_media_a_vd(struct cdev *dev);

#endif