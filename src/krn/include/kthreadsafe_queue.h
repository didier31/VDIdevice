#ifndef __KTHREADSAFE_QUEUE_H__
#define __KTHREADSAFE_QUEUE_H__

#include <sys/param.h>
#include <sys/_stdint.h>


/*
 Producters/Consumers : I/O tasks queue
*/

 template<typename T, size_t capacity> class queue {
    size_t lastAllocated = -1;
    size_t nextFree = 0;
    T buffer[capacity];

    public:
    T exit();
    void enter(T a);
    };

#endif