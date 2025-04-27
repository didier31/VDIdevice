#ifndef __IO_QUEUE_H__
#define __IO_QUEUE_H__

#include "src/krn/include/kthreadsafe_queue.h"
#include "src/include/vdmc.h"

DEFINE_DECLARE_IO_QUEUE kthreadsafe_queue<struct krn_request_t, 512> io_requests;

#endif