    #include <stdio.h>
    #include "VBoxCAPIGlue.h"

int main(int argc, char* argv[])
{
    IVirtualBoxClient *vboxclient = NULL;
    nsresult rc;
    IVirtualBox *virtualBox = NULL;
    ISession *session = NULL;
    IMedium **mediaArray = NULL;
    PRUint32 count = 0;
    /*
    * VBoxCGlueInit() loads the necessary dynamic library, handles errors
    * (producing an error message hinting what went wrong) and gives you
    * the pointer to the function table (g_pVBoxFuncs).
    *
    * Once you get the function table, then how and which functions
    * to use is explained below.
    *
    * g_pVBoxFuncs->pfnClientInitialize does all the necessary startup
    * action and provides us with pointers to an IVirtualBoxClient instance.
    * It should be matched by a call to g_pVBoxFuncs->pfnClientUninitialize()
    * when done.
    */
    if (VBoxCGlueInit())
    {
    fprintf(stderr, "s: FATAL: VBoxCGlueInit failed: %s\n",
    argv[0]);
    return 1;
    }
    g_pVBoxFuncs->pfnClientInitialize(NULL, &vboxclient);
    if (!vboxclient)
    {
    fprintf(stderr, "%s: FATAL: could not get VirtualBoxClient reference\n",
    argv[0]);
    return 1;
    }

    IVirtualBox* aVirtualBox;

    rc = IVirtualBoxClient_GetVirtualBox(vboxclient, &aVirtualBox);
    if (NS_FAILED(rc)) {
        fprintf(stderr, "Erreur lors de la récupération des disques\n");
        IVirtualBox_Release(vboxclient);
        return 1;
    }

    // Lister les médias (IMedium)
    rc = (aVirtualBox)->lpVtbl->GetHardDisks(aVirtualBox, &count, &mediaArray);
    if (NS_FAILED(rc)) {
        fprintf(stderr, "Erreur lors de la récupération des disques\n");
        IVirtualBox_Release(vboxclient);
        return 1;
    }

    printf("Disques virtuels enregistrés : %d\n", count);
    for (PRUint32 i = 0; i < count; i++) {
        IMedium *medium = mediaArray[i];
        BSTR id = NULL, location = NULL;

        IMedium_GetId(medium, &id);
        IMedium_GetLocation(medium, &location);

        wprintf(L"ID:%us\n", id);
        wprintf(L"Chemin: %s\n\n", location);

        IMedium_Release(medium);
    }

    // Libération mémoire
    
    IVirtualBox_Release(vboxclient);
    return 0;
}