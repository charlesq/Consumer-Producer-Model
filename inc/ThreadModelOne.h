#ifndef __THREAD_MODEL_ONE__
#define __THREAD_MODEL_ONE__

#include "ThreadModelBase.h"

class ThreadModelOne: public ThreadModelBase
{
public:
   explicit ThreadModelOne (size_t numOfConsumers = 1, size_t numOfProducers = 1, size_t numofItems = 1);
   virtual ~ThreadModelOne()=default;

private: 
    std::shared_ptr<BufferQueue> filled_;
    std::shared_ptr<BufferQueue> unfilled_;


};



#endif
