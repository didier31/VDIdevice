#include <iconv.h>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <err.h>
#include <sys/ioctl.h>
#include <fcntl.h>

/*
 * Include the XPCOM headers
 */
#include <nsEventQueueUtils.h>
#include <nsIServiceManager.h>
#include <nsMemory.h>
#include <nsString.h>

#include <nsIExceptionService.h>

/*
 * VirtualBox XPCOM interface. This header is generated
 * from IDL which in turn is generated from a custom XML format.
 */
#include "VirtualBox_XPCOM.h"
#include "io.h"
#include "vdmc.h"

/*
 * Prototypes
 */

char *nsIDToString(nsID *guid);
void printErrorInfo();

static volatile int running = 1;

void handle_signal(int sig) { running = 0; }

//
///////////////////////////////////////////////////////////////////////////////
nsCOMPtr<IMediumIO> &handle(uint16_t minor) {
  static nsCOMPtr<IMediumIO>
      handles[std::numeric_limits<std::int16_t>::max() + 1] = {nsnull};
  return handles[minor];
}

// main
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
  /*
   * Check that PRUnichar is equal in size to what compiler composes L""
   * strings from; otherwise NS_LITERAL_STRING macros won't work correctly
   * and we will get a meaningless SIGSEGV. This, of course, must be checked
   * at compile time in xpcom/string/nsTDependentString.h, but XPCOM lacks
   * compile-time assert macros and I'm not going to add them now.
   */
  if (sizeof(PRUnichar) != sizeof(wchar_t)) {
    printf("Error: sizeof(PRUnichar) {%lu} != sizeof(wchar_t) {%lu}!\n"
           "Probably, you forgot the -fshort-wchar compiler option.\n",
           (unsigned long)sizeof(PRUnichar), (unsigned long)sizeof(wchar_t));
    return -1;
  }

  char szTmp[8192];
  if (!getenv("VBOX_XPCOM_HOME")) {
    strcpy(szTmp, argv[0]);
    *strrchr(szTmp, '/') = '\0';
    strcat(szTmp, "/..");
    fprintf(stderr,
            "tstVBoxAPIXPCOM: VBOX_XPCOM_HOME is not set, using '%s' instead\n",
            szTmp);
    setenv("VBOX_XPCOM_HOME", szTmp, 1);
  }
  nsresult rc;
  nsCOMPtr<nsIServiceManager> serviceManager;
  rc = NS_InitXPCOM2(getter_AddRefs(serviceManager), nsnull, nsnull);
  if (NS_FAILED(rc)) {
    printf("Error: XPCOM could not be initialized! rc=%#x\n", rc);
    return -1;
  }
  nsCOMPtr<nsIEventQueue> eventQ;
  rc = NS_GetMainEventQ(getter_AddRefs(eventQ));
  if (NS_FAILED(rc)) {
    printf("Error: could not get main event queue! rc=%#x\n", rc);
    return -1;
  }
  nsCOMPtr<nsIComponentManager> manager;
  rc = NS_GetComponentManager(getter_AddRefs(manager));
  if (NS_FAILED(rc)) {
    printf("Error: could not get component manager! rc=%#x\n", rc);
    return -1;
  }

  nsCOMPtr<IVirtualBox> virtualBox;
  rc = manager->CreateInstanceByContractID(NS_VIRTUALBOX_CONTRACTID, nsnull,
                                           NS_GET_IID(IVirtualBox),
                                           getter_AddRefs(virtualBox));
  if (NS_FAILED(rc)) {
    printf("Error, could not instantiate VirtualBox object! rc=%#x\n", rc);
    return -1;
  }
  printf("VirtualBox object created\n");

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // Gestion des signaux
  signal(SIGTERM, handle_signal);
  signal(SIGINT, handle_signal);

  int fd = open("/dev/vdctl", O_RDWR);
  int i;
  pid_t ownpid = getpid();
  if (fd < 0)
    err(1, "open(/dev/vdctl)");
  printf("srv: My own pid is %d\n", ownpid);
  i = ioctl(fd, IOCTL_INTRODUCE_DAEMON, &ownpid);
  if (i < 0)
    err(1, "ioctl(/dev/vdctl)");
  while (running) {
    nsCOMPtr<IMedium> medium;
    handle(0) = newVirtualDevice(
        virtualBox,
        NS_LITERAL_STRING(
            "/home/didier/VirtualBox VMs/Waydroid/NewVirtualDisk.vdi")
            .get());
    /*
     * Process events that might have queued up in the XPCOM event
     * queue. If we don't process them, the server might hang.
     */
    eventQ->ProcessPendingEvents();
  }
  /* this is enough to free the IVirtualBox instance -- smart pointers rule!
   */
  virtualBox = nsnull;

  /*
   * Perform the standard XPCOM shutdown procedure.
   */
  NS_ShutdownXPCOM(nsnull);
  printf("Done!\n");
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//// Helpers
//////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Helper function to convert an nsID into a human readable string
 *
 * @returns result string, allocated. Has to be freed using free()
 * @param   guid Pointer to nsID that will be converted.
 */
char *nsIDToString(nsID *guid) {
  char *res = (char *)malloc(39);

  if (res != NULL) {
    snprintf(res, 39, "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
             guid->m0, (PRUint32)guid->m1, (PRUint32)guid->m2,
             (PRUint32)guid->m3[0], (PRUint32)guid->m3[1],
             (PRUint32)guid->m3[2], (PRUint32)guid->m3[3],
             (PRUint32)guid->m3[4], (PRUint32)guid->m3[5],
             (PRUint32)guid->m3[6], (PRUint32)guid->m3[7]);
  }
  return res;
}

/**
 * Helper function to print XPCOM exception information set on the current
 * thread after a failed XPCOM method call. This function will also print
 * extended VirtualBox error info if it is available.
 */
void printErrorInfo() {
  nsresult rc;

  nsCOMPtr<nsIExceptionService> es;
  es = do_GetService(NS_EXCEPTIONSERVICE_CONTRACTID, &rc);
  if (NS_SUCCEEDED(rc)) {
    nsCOMPtr<nsIExceptionManager> em;
    rc = es->GetCurrentExceptionManager(getter_AddRefs(em));
    if (NS_SUCCEEDED(rc)) {
      nsCOMPtr<nsIException> ex;
      rc = em->GetCurrentException(getter_AddRefs(ex));
      if (NS_SUCCEEDED(rc) && ex) {
        nsCOMPtr<IVirtualBoxErrorInfo> info;
        info = do_QueryInterface(ex, &rc);
        if (NS_SUCCEEDED(rc) && info) {
          /* got extended error info */
          printf("Extended error info (IVirtualBoxErrorInfo):\n");
          PRInt32 resultCode = NS_OK;
          info->GetResultCode(&resultCode);
          printf("  resultCode=%08X\n", resultCode);
          nsXPIDLString component;
          info->GetComponent(getter_Copies(component));
          printf("  component=%s\n", NS_ConvertUTF16toUTF8(component).get());
          nsXPIDLString text;
          info->GetText(getter_Copies(text));
          printf("  text=%s\n", NS_ConvertUTF16toUTF8(text).get());
        } else {
          /* got basic error info */
          printf("Basic error info (nsIException):\n");
          nsresult resultCode = NS_OK;
          ex->GetResult(&resultCode);
          printf("  resultCode=%08X\n", resultCode);
          nsXPIDLCString message;
          ex->GetMessage(getter_Copies(message));
          printf("  message=%s\n", message.get());
        }

        /* reset the exception to NULL to indicate we've processed it */
        em->SetCurrentException(NULL);

        rc = NS_OK;
      }
    }
  }
}