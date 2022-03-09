#include <thread>
#include <functional>
#include <mutex>
#include <iostream>
#include <chrono>
#include <stdexcept>

void func_2(int& x) {
    while (true) {
        try{
            std::cout << x << '\n';
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        catch (std::runtime_error& e) {
            throw e.what();
        }
    }
}

void func_1() {
   int x = 5;
   std::thread thread_2(func_2, std::ref(x));
   thread_2.detach();
   std::this_thread::sleep_for(std::chrono::milliseconds(2000));
   std::cout << "thread_1 finished executrion \n";
}


int main() {

    std::thread thread_1(func_1);
    thread_1.join();

    return 0;
}