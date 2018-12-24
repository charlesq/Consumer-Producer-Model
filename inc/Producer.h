#ifndef __PRODUCER_H__
#define __PRODUCER_H__
#include "Worker.h"
class Producer: public Worker
{
public:
    Producer(std::shared_ptr<BufferQueue > & contentQ_, std::shared_ptr< BufferQueue>  &blankQ_, const bool &signalStop, std::string name);
    virtual bool isConsumer(void) const final {return false; }
    virtual void work(void);
    virtual std::shared_ptr<BufferItem>  acquireBuffer(void);
    virtual void produce(std::shared_ptr<BufferItem> & buf); 

};


#endif
