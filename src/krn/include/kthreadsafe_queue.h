#ifndef __KTHREADSAFE_QUEUE_H__
#define __KTHREADSAFE_QUEUE_H__

extern "C" {
#include <sys/condvar.h>
#include <sys/mutex.h>
#include <sys/conf.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <sys/_stdint.h>
}

/*
 Producters/Consumers : I/O tasks queue
*/

template <typename T, size_t capacity> class kthreadsafe_queue {

  struct mtx allocMtx, deallocMtx, dataMtx;
  // struct cv allocCV, deallocCV;
  size_t firstAllocated = 0;
  size_t firstFree =
      0; // So, the set of allocated slice is the interval [ firstAllocated,
         // firstFree [ or the [ firstAllocated, capacity [ U [ 0, firstFree [
  T buffer[capacity];
  size_t allocatedCount = 0;

public:
  __attribute__((noinline)) __attribute__((visibility("default")))
  kthreadsafe_queue() {
    char description[51];
    snprintf(description, 51, "kthreadsafe_queue (%p) 's dataMtx", this);
    mtx_init(&dataMtx, description, NULL, MTX_DEF);
    snprintf(description, 51, "kthreadsafe_queue (%p) 's allocMtx", this);
    mtx_init(&allocMtx, description, NULL, MTX_DEF);
    snprintf(description, 51, "kthreadsafe_queue (%p) 's deallocMtx", this);
    mtx_init(&deallocMtx, description, NULL, MTX_DEF);
    /*    snprintf(description, 51, "kthreadsafe_queue (%p) 's allocMtx", this);
        cv_init(&allocCV, description);
        snprintf(description, 51, "kthreadsafe_queue (%p) 's deallocMtx", this);
        cv_init(&deallocCV, description);*/
  }
  __attribute__((noinline)) __attribute__((used))
  __attribute__((visibility("default"))) T
  exit() {
    mtx_lock(&deallocMtx);
    if (allocatedCount <= 0) {
      mtx_lock(&deallocMtx);
    }
    mtx_lock(&dataMtx);
    T r = buffer[firstAllocated];
    firstAllocated++;
    firstAllocated %= capacity;
    allocatedCount--;
    mtx_unlock(&dataMtx);
    mtx_unlock(&deallocMtx);
    return r;
  }

  __attribute__((noinline)) __attribute__((used))
  __attribute__((visibility("default"))) void
  enter(T a) {
    mtx_lock(&allocMtx);
    if (allocatedCount >= capacity) {
      mtx_lock(&allocMtx);
    }
    mtx_lock(&dataMtx);
    buffer[firstFree++] = a;
    firstFree++;
    firstFree %= capacity;
    allocatedCount++;
    mtx_unlock(&dataMtx);
    mtx_unlock(&allocMtx);
  }

  __attribute__((noinline))
  __attribute__((visibility("default"))) ~kthreadsafe_queue() {
    mtx_destroy(&dataMtx);
    mtx_destroy(&allocMtx);
    mtx_destroy(&deallocMtx);
  }
};
#endif
