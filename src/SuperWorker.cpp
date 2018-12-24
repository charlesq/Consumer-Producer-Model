#include "../inc/SuperWorker.h"
SuperWorker::SuperWorker(std::pair<std::shared_ptr<BufferQueue>, std::shared_ptr<BufferQueue> >  consumer_part, std::pair<std::shared_ptr<BufferQueue>, std::shared_ptr<BufferQueue>>  producer_part, const bool &signalStop, std::string name)
:Consumer(consumer_part.first, consumer_part.second, signalStop, ""),
 Producer(producer_part.first, producer_part.second, signalStop, ""),
halt_(signalStop)
{
    Consumer::setName(std::string("Superworker") + name + "_Consumer_duty");
    Producer::setName(std::string("Superworker") + name + "_Producer_duty");
}



void SuperWorker::work(void)
{
    while (!halt_)
    {


        Consumer::work();
        Producer::work();

    }

}
