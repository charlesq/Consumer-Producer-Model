#ifndef __THREAD_MODEL_DEADLOCK_H__
#define __THREAD_MODEL_DEADLOCK_H__
#include <cstdint>
#include <vector>
#include "ThreadModelBase.h"
#include "SuperWorker.h"

class ThreadModelDeadlock: public ThreadModelBase
{
public:
    ThreadModelDeadlock(size_t numOfSuperUsers, size_t numOfBufferItemsPerQ);
    virtual void run(bool withCV = true);
    
private:
    std::vector<std::shared_ptr<SuperWorker> > superworkers_;
    std::vector<std::shared_ptr<BufferQueue> > unfilled_qs_;
    std::vector<std::shared_ptr<BufferQueue>> filled_qs_;
public:
    ~ThreadModelDeadlock();
};


#endif

