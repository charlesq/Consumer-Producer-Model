#include <thread>
#include <unistd.h>
#include "../inc/ThreadModelBase.h"
#include <iostream>
#include "../inc/utils.h"
#include <chrono>

void ThreadModelBase::halt(void)
{
}


void ThreadModelBase::run(bool withCV)
{
    for (auto &c: consumers_)
        threads_.push_back(std::thread(&Consumer::work, c, withCV));
    for (auto &p: producers_)
        threads_.push_back(std::thread(&Producer::work, p, withCV));
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

