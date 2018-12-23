#include <sstream>
#include "../inc/Producer.h"
#include "../inc/utils.h"

Producer::Producer(std::shared_ptr<BufferQueue> &cQ, std::shared_ptr< BufferQueue> & bQ, const bool &signalStop, std::string name)
:Worker(cQ,bQ, signalStop, std::string("Producer_") + name)
{
}

void Producer::work(void)
{
    int seq = 0;
    while (!halt_)
    {
        std::stringstream ss;
        ss << "[" << getName() << "]: " << "    Atttemps to acquire unfilled buffer " << std::endl;
        printMessage(ss.str());
        ss.clear();
        auto  buf = unfilled_->acquireBuffer();
        if (buf.get() == nullptr)
            continue;
        auto &data = buf->getBuffer();
        data.clear();
        Worker::work(); /* I am not so diligent  and need a rest :-) */
        data.assign(getName() + "_data_" + std::to_string(seq++));
        ss<< "[" << getName() << "]: "  << " PUTS $$$$$$[" <<  buf->getBuffer() << "]$$$$$$ in [BufferItem " << buf->getId()  << "]" << std::endl;
        printMessage(ss.str());
        filled_->releaseBuffer(buf);
    }

}

