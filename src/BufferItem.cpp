#include "../inc/BufferItem.h"


BufferItem::BufferItem(uint16_t id)
: id_ (id)
{
}
uint16_t BufferItem::getId(void) const
{
    return id_;
}

std::string& BufferItem::getBuffer(void)
{
    return data_;
}

const std::string& BufferItem::getBuffer(void) const
{
    return data_;
}

