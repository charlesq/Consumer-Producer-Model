#include "../inc/SuperWorker.h"
SuperWorker::SuperWorker(std::pair<std::shared_ptr<BufferQueue>, std::shared_ptr<BufferQueue> >  consumer_part, std::pair<std::shared_ptr<BufferQueue>, std::shared_ptr<BufferQueue>>  producer_part, const bool &signalStop, std::string name)
:Consumer(consumer_part.first, consumer_part.second, signalStop, ""),
 Producer(producer_part.first, producer_part.second, signalStop, "") 
{
    Consumer::setName(std::string("Superworker") + name);
    Producer::setName(std::string("Superworkder") + name);
}
