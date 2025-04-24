#include "src/krn/include/kthreadsafe_queue.h"

template<typename T, size_t capacity> T queue<T, capacity>::exit()
{

    T r = buffer[firstAllocated];
    firstAllocated++;
    firstAllocated %= capacity;
    return r;
}


template<typename T, size_t capacity> void queue<T, capacity>::enter(T a)
{
    buffer[firstFree++] = a;
    firstFree++;
    firstFree %= capacity;
}