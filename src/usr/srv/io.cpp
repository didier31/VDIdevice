#include <nsString.h>
#include <nsIServiceManager.h>
#include <nsEventQueueUtils.h>

#include <nsIExceptionService.h>

#include "io.h"

 nsCOMPtr<IMediumIO> newVirtualDevice(nsCOMPtr<IVirtualBox> virtualBox, const PRUnichar* pathname)
{
    unsigned short vide[] = { 0 };
    nsCOMPtr<IMedium> medium;
    virtualBox->OpenMedium(pathname, DeviceType_HardDisk, AccessMode_ReadWrite, false, getter_AddRefs(medium));
    nsCOMPtr<IMediumIO> mediumIO;
    medium->OpenForIO(true, vide, getter_AddRefs(mediumIO));
    return mediumIO;
}