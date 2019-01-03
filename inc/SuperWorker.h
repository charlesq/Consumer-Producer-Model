#ifndef __SUPER_WORKER_H__
#define __SUPER_WORKER_H__
#include <utility>
#include "Consumer.h"
#include "Producer.h"
class SuperWorker: public Consumer, public Producer
{
public:
    SuperWorker(void) = delete;
    SuperWorker(std::pair<std::shared_ptr<BufferQueue>, std::shared_ptr<BufferQueue> >  consumer_part, std::pair<std::shared_ptr<BufferQueue>, std::shared_ptr<BufferQueue> >  producer_part, std::string name);

    void work(bool withCV = true);
protected:
};


#endif 
