#include "../inc/BufferQueue.h"

BufferQueue::BufferQueue(const bool &forceOut)
:over_(forceOut)
{
}
void BufferQueue::fillBufferItems(uint16_t numOfBufferItems)
{
    while(numOfBufferItems-- != 0)
    {
        items_.push_back(std::make_shared<BufferItem >(numOfBufferItems));
        push(items_.back());
     }
}

BufferQueue::~BufferQueue()
{
    for (auto &e: items_)
        e.reset();
    items_.clear();

}

std::shared_ptr<BufferItem> BufferQueue::acquireBuffer(void)
{
    std::unique_lock<std::mutex> lk(mtx_);
    // if over_ is true return;
    cv_.wait(lk, [&]{return !this->empty() || over_;});
    auto b =  dequeueBuffer();
    lk.unlock();
    return b;
}
std::shared_ptr<BufferItem> BufferQueue::dequeueBuffer(void)
{
  std::shared_ptr<BufferItem> item;
  if (!empty())
  {
      item = front().lock();
      pop();
  }
  return item;
}

void BufferQueue::queueBuffer(std::shared_ptr<BufferItem> buf)
{
    push(buf);
}
void BufferQueue::releaseBuffer(std::shared_ptr<BufferItem> buf)
{
    std::unique_lock<std::mutex> lk(mtx_);
    queueBuffer(buf);
    lk.unlock();
    cv_.notify_one();
}

