#ifndef __CONSUMER_H__
#define __CONSUMER_H__
#include "Worker.h"

class Consumer: public Worker
{
public:
    Consumer(std::shared_ptr<BufferQueue> & contentQ_, std::shared_ptr<BufferQueue> &blankQ_,std::string name);
    virtual void work(bool withCV = true);
    virtual bool isConsumer(void)  const  { return true; }
    virtual std::shared_ptr<BufferItem>  acquireBuffer(bool withCV = true);
    virtual void consume(const std::shared_ptr<BufferItem>  buf);
    virtual void returnBuffer(std::shared_ptr<BufferItem> buf);

};


#endif
