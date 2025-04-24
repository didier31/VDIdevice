#ifndef __KTHREADSAFE_QUEUE_H__
#define __KTHREADSAFE_QUEUE_H__

#include <sys/param.h>
#include <sys/_stdint.h>


/*
 Producters/Consumers : I/O tasks queue
*/

 template<typename T, size_t capacity> class queue {

    size_t firstAllocated = 0;
    size_t firstFree = 0;   // So, the set of allocated slice is the interval [ firstAllocated, firstFree [ 
                            // or the [ firstAllocated, capacity [ U [ 0, firstFree [
    T buffer[capacity];

    public:
    T exit();
    void enter(T a);
    };

#endif