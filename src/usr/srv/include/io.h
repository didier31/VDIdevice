#ifndef __IO_H__
#define __IO_H__

#include <nsMemory.h>

#include "VirtualBox_XPCOM.h"

nsCOMPtr<IMediumIO> newVirtualDevice(nsCOMPtr<IVirtualBox> virtualBox, const PRUnichar* pathname);

#endif