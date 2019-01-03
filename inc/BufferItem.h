#ifndef __BUFFER_ITEM_H__
#define __BUFFER_ITEM_H__
#include <string>

class BufferItem
{
public:
    BufferItem(void) = delete;
    explicit BufferItem(uint16_t id);
    virtual std::string & getBuffer (void) final;
    virtual const std::string & getBuffer(void) const;
    virtual ~BufferItem() = default;
    virtual uint16_t  getId(void) const;
private:
    std::string data_;
    uint16_t id_;

};


#endif
