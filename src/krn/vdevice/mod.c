#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/param.h>
#include <sys/conf.h>
#include "src/krn/include/vdmc.h"

int vdmc_modevent(module_t mod __unused, int event, void *arg __unused);

moduledata_t vdmc_mod = {"vdmc", vdmc_modevent, NULL};

DECLARE_MODULE(mod, vdmc_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);