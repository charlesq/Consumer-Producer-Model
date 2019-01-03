#include "../inc/ThreadModelDeadlock.h"

ThreadModelDeadlock::ThreadModelDeadlock(size_t numOfSuperWorkers, size_t numOfBufferItemsPerQ)
{

   size_t n = numOfSuperWorkers;
   while (n -- != 0)
   {
       filled_qs_.push_back(std::make_shared<BufferQueue>());
       filled_qs_.back()->setName(std::string("") + "<synchronzed_queue_pair_" + std::to_string(n) + "_filled");
       unfilled_qs_.push_back(std::make_shared<BufferQueue>());
       unfilled_qs_.back()->fillBufferItems(numOfBufferItemsPerQ);
       unfilled_qs_.back()->setName(std::string("") + "<synchronzed_queue_pair_" + std::to_string(n) + "_unfilled");
   }
   for (size_t i = 0; i < numOfSuperWorkers; i ++)
   {
      typedef std::shared_ptr<BufferQueue> BQ;
      auto  c = std::make_pair<BQ, BQ > (std::shared_ptr<BufferQueue> (filled_qs_[i]),  std::shared_ptr<BufferQueue> (unfilled_qs_[i]));
      auto  p = std::make_pair<BQ, BQ > (std::shared_ptr<BufferQueue> (filled_qs_[(i + 1) % numOfSuperWorkers]),  std::shared_ptr<BufferQueue> (unfilled_qs_[(i + 1) % numOfSuperWorkers]));
      superworkers_.push_back(std::make_shared<SuperWorker>(c, p, std::to_string(i)));
   }
 

}

void ThreadModelDeadlock::run(bool withCV)
{
    for (auto &s: superworkers_)
    {
        threads_.push_back(std::thread(&SuperWorker::work, s, withCV));
    }
    for (std::thread & th: threads_)
        if(th.joinable())
           th.join();

}


ThreadModelDeadlock::~ThreadModelDeadlock()
{
   for (auto & q: filled_qs_)
     q.reset();
   filled_qs_.clear();
   for (auto &q: unfilled_qs_)
      q.reset();  
   unfilled_qs_.clear();
   for (auto & w: superworkers_)
     w.reset();
   superworkers_.clear();
}
