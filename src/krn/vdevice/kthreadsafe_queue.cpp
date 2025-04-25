#include "src/krn/include/kthreadsafe_queue.h"

template<typename T, size_t capacity> kthreadsafe_queue<T, capacity>::kthreadsafe_queue()
{
    char description[51];
    snprintf(description, 51, "kthreadsafe_queue (%p) 's myMutex", this);
    mtx_init(&myMutex, description, NULL, MTX_DEF);
}

template<typename T, size_t capacity> kthreadsafe_queue<T, capacity>::~kthreadsafe_queue()
{
    mtx_destroy(&myMutex);
}

template<typename T, size_t capacity> T kthreadsafe_queue<T, capacity>::exit()
{

    T r = buffer[firstAllocated];
    firstAllocated++;
    firstAllocated %= capacity;
    return r;
}

template<typename T, size_t capacity> void kthreadsafe_queue<T, capacity>::enter(T a)
{
    buffer[firstFree++] = a;
    firstFree++;
    firstFree %= capacity;
}