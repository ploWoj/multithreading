#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>

int getRandom(int max)
{
    srand(time(NULL));
    return rand() % max;
}

std::string GetTime()
{
    auto nowTime = std::chrono::system_clock::now();
    std::time_t sleepTime = std::chrono::system_clock::to_time_t(nowTime);
    return std::ctime(&sleepTime);
}

double acctBalance = 100;

std::mutex accLock;

void GetMoney(int id, double withdrawal)
{
    std::lock_guard<std::mutex> lock(accLock);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << id << " tries to withdrawl $ " << withdrawal << " on " << GetTime() << "\n";

    if ((acctBalance - withdrawal) >= 0)
    {
        acctBalance -= withdrawal;
        std::cout << "New Accoun Balanace is $" << acctBalance << "\n";
    }
    else
    {
        std::cout << "Not EnoughMoney in Account\n";
        std::cout << "Current Balance is $" << acctBalance << "\n";
    }
}

int main()
{

    std::thread threads[10];

    for (int i = 0; i < 10; i++)
    {
        threads[i] = std::thread(GetMoney, i, 15);
    }
    for (int i = 0; i < 10; i++)
    {
        threads[i].join();
    }

    return 0;
}