#include "../inc/SuperWorker.h"

 SuperWorker::SuperWorker(std::pair<std::shared_ptr<BufferQueue>, std::shared_ptr<BufferQueue> >  consumer_part, 
                          std::pair<std::shared_ptr<BufferQueue>, std::shared_ptr<BufferQueue>>  producer_part,
                          const bool &signalStop, std::string name) 

:Consumer(consumer_part.first, consumer_part.second, signalStop, ""), 
 Producer(producer_part.first, producer_part.second, signalStop, ""), 
 halt_(signalStop) 

{ 
    Consumer::setName(std::string("Superworker") + name + "_Consumer_duty"); 
    Producer::setName(std::string("Superworker") + name + "_Producer_duty"); 

}

void SuperWorker::work(bool withCV) 
{ 
    while (!halt_) 
    { 
        auto buf = Consumer::acquireBuffer(withCV); 
        Consumer::consume(buf);
        returnBuffer(buf);
        buf = Producer::acquireBuffer(withCV);
        Producer::produce(buf);
        Producer::postBuffer(buf);
    }

}


