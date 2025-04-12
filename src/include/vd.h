#ifndef __VDEVICE__
#define __VDEVICE__
#include <sys/conf.h>

struct cdev* make_media_a_device(char* virtualMediaPathName);
void unmake_media_a_device(struct cdev* dev);

#endif