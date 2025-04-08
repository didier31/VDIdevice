#ifndef __MOD_H__
#define __MOD_H__
#define VS_GROUP 0xAA

struct vs_device_info {
  char *devicePath;
  char *mediaPath;
  enum { __VDI, __VMDK, __QCOW2 } mediaType;
};

struct vs_devices_info {
  unsigned count;
  struct vs_device_info info[];
};

#define NEW_VS_DEVICE_CMD 1
#define DELETE_VS_DEVICE_CMD 2
#define LIST_VS_DEVICES_CMD 3

#define IOCTL_NEW_VS_DEVICE _IOW(VS_GROUP, NEW_VS_DEVICE_CMD, char*)
#define IOCTL_DELETE_VS_DEVICE _IOW(VS_GROUP, DELETE_VS_DEVICE_CMD, char*)
#define IOCTL_LIST_VS_DEVICES _IOR(VS_GROUP, LIST_VS_DEVICES_CMD, struct vs_devices_info*)

#endif