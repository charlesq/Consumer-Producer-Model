#ifndef __CONSUMER_H__
#define __CONSUMER_H__
#include "Worker.h"

class Consumer: public Worker
{
public:
    Consumer(std::shared_ptr<BufferQueue> & contentQ_, std::shared_ptr<BufferQueue> &blankQ_,  const bool &signalStop, std::string name);
    virtual void work(void);
    virtual bool isConsumer(void)  const final   { return true; }
    virtual std::shared_ptr<BufferItem>  acquireBuffer(void);
    virtual void consume(const std::shared_ptr<BufferItem>  buf);

};


#endif
