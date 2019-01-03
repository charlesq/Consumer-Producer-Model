#ifndef __BUFFER_QUEUE_H__
#define __BUFFER_QUEUE_H__

#include <condition_variable>
#include <vector>
#include <memory>
#include <mutex>
#include <queue>
#include "BufferItem.h"

class BufferQueue: private std::queue<std::weak_ptr<BufferItem>>
{
public:
    BufferQueue(void) = default;
    virtual void fillBufferItems(uint16_t numOfBufferItems);
    ~BufferQueue();
    virtual std::shared_ptr<BufferItem> acquireBuffer(std::string user = "", bool withCV = true);

    virtual  void releaseBuffer(std::shared_ptr<BufferItem> buf);
    virtual void setName(std::string n);
    virtual const std::string & getName(void) const;
private:
    std::vector<std::shared_ptr<BufferItem>> items_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::shared_ptr<BufferItem> dequeueBuffer(void);
    void queueBuffer(std::shared_ptr<BufferItem> buf);
    std::string name_; // an added field after ThreadModelOne has been coded
};

#endif
