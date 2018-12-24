#include <sstream>
#include "../inc/Consumer.h"
#include "../inc/utils.h"

Consumer::Consumer(std::shared_ptr<BufferQueue > & cQ, std::shared_ptr<BufferQueue> &bQ, const bool &signalStop, std::string name)
:Worker(cQ,bQ, signalStop, std::string("Consumer_") + name)
{
}
void Consumer::work(void)
{
    while (!halt_)
    {
        std::stringstream ss;
        ss  << "[" << getName() <<  "]: " << "    Attemps to acquire filled  buffer from [" << filled_->getName() << "]" << std::endl;
        printMessage(ss.str());
        ss.clear(); 
        auto  buf = filled_->acquireBuffer();
        if (buf.get() == nullptr)
            continue; 
        ss << "[" << getName() << "]: " << " CONSUMING ******(" <<  buf->getBuffer() << ")****** in [BufferItem " << buf->getId()  << "]"  << std::endl;
        printMessage(ss.str());
        ss.clear();
        Worker::work(); // need a break;
        ss << "[" << getName() << "]: " << " RELEASED   ******[BufferItem " << buf->getId() << "]" << " to [" << unfilled_->getName() << "]" << std::endl; 
        printMessage(ss.str());
        unfilled_->releaseBuffer(buf);
        Worker::work();
      
    }
}


