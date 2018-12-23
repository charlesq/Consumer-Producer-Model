#include "../inc/ThreadModelOne.h"



ThreadModelOne::ThreadModelOne(size_t numOfConsumers, size_t numOfProducers, size_t numOfItems)
{
    filled_.reset(new BufferQueue(halt_));
    unfilled_.reset(new BufferQueue(halt_));
    unfilled_->fillBufferItems(numOfItems);
    while(numOfConsumers-- != 0)
    {
         std::shared_ptr<Consumer> p(new Consumer(filled_, unfilled_, halt_, std::to_string(numOfConsumers)));
         consumers_.push_back(p);
         consumers_.push_back(std::shared_ptr<Consumer>(new Consumer(filled_, unfilled_, halt_, std::to_string(numOfConsumers))));
    }
    while(numOfProducers-- != 0)
    {
        producers_.push_back(std::shared_ptr<Producer>(new Producer(filled_, unfilled_, halt_, std::to_string(numOfProducers))));
    }

}

