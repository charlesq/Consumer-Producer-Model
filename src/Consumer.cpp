#include <sstream>
#include "../inc/Consumer.h"
#include "../inc/utils.h"

Consumer::Consumer(std::shared_ptr<BufferQueue > & cQ, std::shared_ptr<BufferQueue> &bQ, std::string name)
:Worker(cQ,bQ, std::string("Consumer_") + name)
{
}
void Consumer::work(bool withCV)
{
    std::stringstream ss;
    while (true)
    {
        auto buf = acquireBuffer(withCV);
        consume(buf); 
        returnBuffer(buf);
      
    }
}


std::shared_ptr<BufferItem>   Consumer::acquireBuffer(bool withCV) 
{
    std::stringstream ss;
    ss  << "[" << getName() <<  "]: " << "    Attemps to acquire filled  buffer from [" << filled_->getName() << "]" << std::endl;
    printMessage(ss.str());
    ss.clear(); 
    auto  buf = filled_->acquireBuffer(getName(), withCV);
    if (buf.get() == nullptr)
    {
        ss << "[" << getName() << "]: " << " GOT NO FILLED BUFFER from " << "[" << filled_->getName() << "]" << std::endl;
        printMessage(ss.str());
    }
    return buf;
}

void Consumer::returnBuffer(std::shared_ptr<BufferItem> buf)
{
   if (buf.get() == nullptr)
       return;
   std::stringstream ss;
   ss << "[" << getName() << "]: " << " RELEASED   ******[BufferItem " << buf->getId() << "]" << " to [" << unfilled_->getName() << "]" << std::endl; 
   printMessage(ss.str());
   unfilled_->releaseBuffer(buf);
}  

void Consumer::Consumer::consume(const std::shared_ptr<BufferItem> buf)
{ 
     std::stringstream ss;
     if (buf.get() == nullptr) return;
     ss << "[" << getName() << "]: " << " CONSUMING ******(" <<  buf->getBuffer() << ")****** in [BufferItem " << buf->getId()  << "]"  << std::endl;
     printMessage(ss.str());
     Worker::work(); // need a break;
}
