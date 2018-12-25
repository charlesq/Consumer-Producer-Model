#ifndef __PRODUCER_H__
#define __PRODUCER_H__
#include "Worker.h"
class Producer: public Worker
{
public:
    Producer(std::shared_ptr<BufferQueue > & contentQ_, std::shared_ptr< BufferQueue>  &blankQ_, const bool &signalStop, std::string name);
    virtual bool isConsumer(void) const final {return false; }
    virtual void work(bool withCV = true);
    virtual std::shared_ptr<BufferItem>  acquireBuffer(bool withCV = true);
    virtual void produce(std::shared_ptr<BufferItem> & buf); 
    virtual void postBuffer(std::shared_ptr<BufferItem> buf);

};


#endif
