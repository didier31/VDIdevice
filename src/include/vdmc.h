#ifndef __MOD_H__
#define __MOD_H__

#include <sys/_stdint.h>

#define VS_GROUP 0xAA

struct vs_device_info {
  char *devicePath;
  char *mediaPath;
  enum { __VDI, __VMDK, __QCOW2 } mediaType;
};

/*
Communication requests to kernel
*/
struct vs_devices_info {
  unsigned count;
  struct vs_device_info info[];
};

struct data_io_request {
  uint16_t minor;
  size_t bufferSize;
};

#define NEW_VS_DEVICE_CMD 1
#define DELETE_VS_DEVICE_CMD 2
#define LIST_VS_DEVICES_CMD 3
#define WRITE_VD_CMD 4
#define READ_VD_CMD 5

#define IOCTL_NEW_VS_DEVICE _IOW(VS_GROUP, NEW_VS_DEVICE_CMD, char *)
// Arg : uint16_t minor
#define IOCTL_DELETE_VS_DEVICE _IOW(VS_GROUP, DELETE_VS_DEVICE_CMD, uint16_t)
#define IOCTL_LIST_VS_DEVICES _IOR(VS_GROUP, LIST_VS_DEVICES_CMD, struct vs_devices_info*)
#define IOCTL_READ_VD _IOWR(VS_GROUP, READ_VD_CMD, struct vs_devices_info*)
#define IOCTL_WRITE_VD _IOWR(VS_GROUP, WRITE_VD_CMD, struct vs_devices_info*)

/*
Communication from daemon to kernel
*/

#define KRN_REQUEST_CMD 6
// Arg : result of thr_self()

struct krn_request {
  enum REQUEST_TYPE {
    READ_VD = 0,
    WRITE_VD = 1,
    LIST_DEVICES = 2,
    NEW_DEVICE = 3,
    DELETE_DEVICE = 4
  } type;
  union {
    struct {
      size_t size;
      void *ptr;
    } io_buffer;
    struct {
      char *pathname;
      uint16_t minor;
    } new_device;
    char *pathnames[1 << sizeof(uint16_t)*8];
  } payload;
};

#define IOCTL_KRN_REQUEST _IORW(VS_GROUP, KRN_REQUEST_CMD, struct krn_request*)

#endif