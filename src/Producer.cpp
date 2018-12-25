#include <sstream>
#include "../inc/Producer.h"
#include "../inc/utils.h"

Producer::Producer(std::shared_ptr<BufferQueue> &cQ, std::shared_ptr< BufferQueue> & bQ, const bool &signalStop, std::string name)
:Worker(cQ,bQ, signalStop, std::string("Producer_") + name)
{
}

void Producer::work(bool withCV)
{
    std::stringstream ss;
    int seq = 0;
    while (!halt_)
    {
        auto buf = acquireBuffer(withCV);
       produce(buf);
       postBuffer(buf);
    }

}


std::shared_ptr<BufferItem>  Producer::acquireBuffer(bool withCV)
{
    std::stringstream ss;
    ss << "[" << getName() << "]: " << "    Atttemps to acquire unfilled buffer from [" << unfilled_->getName() << "]" << std::endl;
    printMessage(ss.str());
    ss.clear();
    auto buf = unfilled_->acquireBuffer(getName(), withCV);
    if (buf.get() == nullptr)
    {
        ss << "[" << getName() << "]: " << " GOT NO UNFILLED BUFFER from " << "[" << filled_->getName() << "]" << std::endl;
        printMessage(ss.str());
        ss.clear();
    } 
    Worker::work();
    return buf;
}



void Producer::produce(std::shared_ptr<BufferItem> & buf)
{
    static size_t seq = 0;
    std::stringstream ss;
    if (buf.get() == nullptr)
        return;
    auto &data = buf->getBuffer();
    data.clear();
    data.assign(getName() + "_data_" + std::to_string(seq++));
    ss<< "[" << getName() << "]: "  << " PRODUCING   $$$$$$[" <<  buf->getBuffer() << "]$$$$$$ in [BufferItem " << buf->getId()  << "]" << std::endl;
    printMessage(ss.str());
    ss.clear();
    Worker::work(); /* I am not so diligent  and need a rest :-) */ 

}

void Producer::postBuffer(std::shared_ptr<BufferItem>  buf)
{
    std::stringstream ss;
    if (buf.get() == nullptr)
        return;
    ss << "[" << getName() << "]: " << " POSTED       $$$$$$[BufferItem " << buf->getId() << " to [" << filled_->getName() << "]" << std::endl; 
    printMessage(ss.str());
    filled_->releaseBuffer(buf); 
    Worker::work();

}
