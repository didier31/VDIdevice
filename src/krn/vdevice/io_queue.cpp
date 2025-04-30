#include "src/krn/include/io_queue.h"

extern "C" {
    #include <sys/conf.h>
    #include <sys/param.h>
    #include <sys/systm.h>
    #include <sys/types.h>
    #include <sys/malloc.h>
    #include <sys/kernel.h>
    }

MALLOC_DEFINE(M_IO_QUEUE, "io_requests", "io_requests allocation");

io_requests_t* io_requests = nullptr;