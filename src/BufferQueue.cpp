#include <memory>
#include <string>
#include "../inc/BufferQueue.h"
#include "../inc/utils.h"

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

std::shared_ptr<BufferItem> BufferQueue::acquireBuffer(std::string user, bool withCV)
{
    std::unique_lock<std::mutex> lk(mtx_);
    if (withCV)
        cv_.wait(lk, [&]{return !this->empty() ;});
    printMessage(std::string("[") + user + "]:" + "  LOCKED on " + getName() + "\n");
    auto b =  dequeueBuffer();
    return b;
}

std::shared_ptr<BufferItem>  BufferQueue::dequeueBuffer(void)
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
    std::lock_guard<std::mutex> lk(mtx_);
    queueBuffer(buf);
    cv_.notify_one();
}

void BufferQueue::setName(std::string n)
{
    name_ = n;
}

const std::string & BufferQueue::getName(void) const
{
   return name_;
}
