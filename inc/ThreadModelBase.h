#ifndef __THREAD_MODEL_BASE_H__
#define __THREAD_MODEL_BASE_H__
#include <thread>
#include <memory>
#include "Consumer.h"
#include "Producer.h"

class ThreadModelBase
{
public:
     void halt();
     inline size_t getNumberOfConsumers(void) const;
     inline size_t getNumberOfProducers(void) const;
     virtual ~ThreadModelBase();
     virtual void run(bool withCV = true);

protected:

    std::vector<std::shared_ptr<Consumer>> consumers_;
    std::vector<std::shared_ptr<Producer>> producers_;
    bool halt_ = true;
    std::vector<std::thread > threads_;
    ThreadModelBase() = default;

};


#endif
