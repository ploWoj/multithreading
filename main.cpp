#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

int i = 0;
std::mutex mu;
std::condition_variable cv;
bool shouldIncrement = true;


void incr() 
{
    while(true) {
        std::unique_lock<std::mutex> lu (mu);
        cv.wait(lu, []{return shouldIncrement;} );
        std::cout << i << '\n';
        shouldIncrement = false;
        lu.unlock();
        cv.notify_all();
    }
}

void printOdd() 
{
    while(true) {
        std::unique_lock<std::mutex> lu (mu);
        cv.wait( lu, []{ return i % 2 == 1 && !shouldIncrement; } );

        std::cout << "printOdd: " << i << '\n';
        shouldIncrement = true;
        lu.unlock();
        cv.notify_one();
    }
}

void printEven() 
{
    while(true)
    {
        std::unique_lock<std::mutex> lu( mu );
        cv.wait( lu, [] { return i % 2 == 1 && !shouldIncrement;} );
        std::cout << "printEven: " << i << '\n';
        shouldIncrement = true;
        lu.unlock();
        cv.notify_all();
    }
}

int main() 
{
    std::thread increm { incr };
    std::thread t1 { printEven };
    std::thread t2 { printOdd };
    increm.join();
    t1.join();
    t2.join();
}