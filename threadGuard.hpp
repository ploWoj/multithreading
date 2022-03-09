#pragma once

#include <thread>
#include <vector>

class thread_guard
{
private:
    std::thread &t_;

public:
    explicit thread_guard(std::thread &t);

    ~thread_guard();

    thread_guard(const thread_guard &t) = delete;
    thread_guard &operator=(const thread_guard &t) = delete;

    thread_guard(thread_guard &&other);
    thread_guard &operator=(thread_guard &&other);
};