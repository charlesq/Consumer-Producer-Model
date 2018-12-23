#include <mutex>
#include <iostream>
#include "../inc/utils.h"
void printMessage(const std::string &m)
{
    static std::mutex g_mtx;
    std::lock_guard<std::mutex>  l_(g_mtx);
    std::cout << m;
}

