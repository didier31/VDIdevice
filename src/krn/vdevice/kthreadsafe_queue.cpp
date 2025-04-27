#include "src/krn/include/kthreadsafe_queue.h"

#include <sys/condvar.h>


template<typename T, size_t capacity> kthreadsafe_queue<T, capacity>::kthreadsafe_queue()
{
    char description[51];
    snprintf(description, 51, "kthreadsafe_queue (%p) 's allocMtx", this);
    mtx_init(&allocMtx, description, NULL, MTX_DEF);
    snprintf(description, 51, "kthreadsafe_queue (%p) 's deallocMtx", this);
    mtx_init(&deallocMtx, description, NULL, MTX_DEF);
    snprintf(description, 51, "kthreadsafe_queue (%p) 's allocMtx", this);
    cv_init(&allocCV, description);
    snprintf(description, 51, "kthreadsafe_queue (%p) 's deallocMtx", this);
    cv_init(&deallocCV, description);
}

template<typename T, size_t capacity> kthreadsafe_queue<T, capacity>::~kthreadsafe_queue()
{
    mtx_destroy(&allocMtx);
    mtx_destroy(&deallocMtx);
}

template<typename T, size_t capacity> T kthreadsafe_queue<T, capacity>::exit()
{
    mtx_lock(&allocMtx);
    if (allocatedCount > 0)
    {
        cv_wait(&deallocCV, &allocMtx);
    }
    T r = buffer[firstAllocated];
    firstAllocated++;
    firstAllocated %= capacity;
    allocatedCount--;
    mtx_unlock(&allocMtx);
    cv_signal(&allocCV);
    return r;
}

template<typename T, size_t capacity> void kthreadsafe_queue<T, capacity>::enter(T a)
{
    mtx_lock(&deallocMtx);
    if (allocatedCount >= capacity)
    {
        cv_wait(&allocCV, &allocMtx);
    }
    buffer[firstFree++] = a;
    firstFree++;
    firstFree %= capacity;
    allocatedCount++;
    mtx_unlock(&deallocMtx);
    cv_signal(&deallocCV);
}