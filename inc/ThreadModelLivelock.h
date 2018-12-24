#ifndef __THREAD_MODEL_LIVE_LOCK_H__
#define __THREAD_MODEL_LIVE_LOCK_H__

#include <cstdint>
#include <vector>
#include "ThreadModelBase.h"
#include "SuperWorker.h"

class ThreadModelLivelock: public ThreadModelBase
{
public:
    ThreadModelLivelock(size_t numOfSuperUsers, size_t numOfBufferItemsPerQ);
    virtual void run(void);
private:
    std::vector<std::shared_ptr<SuperWorker> > superworkers_;
    std::vector<std::shared_ptr<BufferQueue> > unfilled_qs_;
    std::vector<std::shared_ptr<BufferQueue>> filled_qs_;
public:
    ~ThreadModelLivelock();
};


#endif
