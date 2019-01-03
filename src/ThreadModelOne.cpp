#include "../inc/ThreadModelOne.h"



ThreadModelOne::ThreadModelOne(size_t numOfConsumers, size_t numOfProducers, size_t numOfItemsPerQ)
{
    filled_= std::make_shared<BufferQueue> ();
    filled_->setName("Paired_BufferQueue_0_filled");
    unfilled_ =  std::make_shared<BufferQueue>();
    unfilled_->fillBufferItems(numOfItemsPerQ);
    unfilled_->setName("Paired_Buffer_Queue_0_unfilled");
    while(numOfConsumers-- != 0)
    {
         consumers_.push_back(std::make_shared<Consumer>(filled_, unfilled_, std::to_string(numOfConsumers)));
    }
    while(numOfProducers-- != 0)
    {
        producers_.push_back(std::make_shared<Producer>(filled_, unfilled_, std::to_string(numOfProducers)));
    }

}


