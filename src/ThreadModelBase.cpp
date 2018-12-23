#include <thread>
#include "../inc/ThreadModelBase.h"

void ThreadModelBase::halt(void)
{
    halt_ = true;
}


void ThreadModelBase::run()
{
    halt_ = false;
    for (auto &c: consumers_)
        threads_.push_back(std::thread(&Consumer::work, c));
    for (auto &p: producers_)
        threads_.push_back(std::thread(&Producer::work, p));
    for (std::thread & th: threads_)
        if(th.joinable())
           th.join();
}
ThreadModelBase::~ThreadModelBase()
{
    for (auto &c: consumers_)
        c.reset();
    consumers_.clear();
    for (auto &p: producers_)
        p.reset();
    producers_.clear();
    threads_.clear();

}
size_t ThreadModelBase::getNumberOfConsumers(void) const
{
    return consumers_.size();
}

size_t ThreadModelBase::getNumberOfProducers(void) const
{
    return producers_.size();
}

