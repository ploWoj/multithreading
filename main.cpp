#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <stdexcept>

#include "threadGuard.hpp"

void test()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "Hello from test \n";
}

void bar()
{
    std::cout << "This is other operation \n";
    throw std::runtime_error("this is a runtime error");
}

void run()
{
    std::thread foo_thread(test);
    thread_guard tg(foo_thread);

    try
    {
        bar();
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what();
    }
}

int main()
{
    run();
    return 0;
}