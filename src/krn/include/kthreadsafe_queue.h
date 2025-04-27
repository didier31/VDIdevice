#ifndef __KTHREADSAFE_QUEUE_H__
#define __KTHREADSAFE_QUEUE_H__

#include <sys/param.h>
#include <sys/_stdint.h>
#include <sys/mutex.h>
#include <sys/condvar.h>


/*
 Producters/Consumers : I/O tasks queue
*/

 template<typename T, size_t capacity> class kthreadsafe_queue {

    struct mtx allocMtx, deallocMtx;
    struct cv allocCV, deallocCV;
    size_t firstAllocated = 0;
    size_t firstFree = 0;   // So, the set of allocated slice is the interval [ firstAllocated, firstFree [ 
                            // or the [ firstAllocated, capacity [ U [ 0, firstFree [
    T buffer[capacity];
    size_t allocatedCount = 0;

    public:
    kthreadsafe_queue();
    T exit();
    void enter(T a);
    ~kthreadsafe_queue();
    };

#endif