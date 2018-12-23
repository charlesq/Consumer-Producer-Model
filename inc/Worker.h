#ifndef __WORKER_H__
#define __WORKER_H__

#include <unistd.h>
#include "BufferQueue.h"

class Worker
{
public:
    Worker() = delete;
    explicit Worker(std::shared_ptr<BufferQueue >& contentQ_, std::shared_ptr<BufferQueue > &blankQ_, const bool &signalStop, std::string name = "default worker");
    virtual void work(void) { sleep(latency_);}
    virtual bool isConsumer(void) const { throw "undefined"; }
    virtual const std::string & getName() const final {return name_;}
    virtual void setEfficiency(size_t l) final { latency_ = l;}

protected:
    std::shared_ptr<BufferQueue> filled_;
    std::shared_ptr<BufferQueue> unfilled_;
    std::string name_;
    const bool & halt_;
    int latency_ = 2; // in seconds,be default need 2 seconds to finish work;
};

#endif
