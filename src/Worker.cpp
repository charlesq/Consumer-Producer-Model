#include <iostream>
#include "../inc/Worker.h"

Worker::Worker(std::shared_ptr<BufferQueue> & cQ, std::shared_ptr<BufferQueue>& bQ, const bool &signalStop, std::string name)
:filled_(cQ),
 unfilled_(bQ),
 name_(name),
 halt_(signalStop)
{
    if (filled_ == nullptr && unfilled_ == nullptr)
    {
        std::cout << "error at " <<  __func__ << " in " <<  __FILE__ << ": neither queue can be null" << std::endl;
        throw "exception in Worker::Worker";

    }
}

void Worker::setName(std::string name)
{
    name_ = name;
}

