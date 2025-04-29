#ifndef __IO_QUEUE_H__
#define __IO_QUEUE_H__

#include "src/krn/include/kthreadsafe_queue.h"
#include "src/include/vdmc.h"

template class kthreadsafe_queue<struct krn_request_t, 512>;

typedef kthreadsafe_queue<struct krn_request_t, 512> io_requests_t;

extern io_requests_t io_requests;

#endif