
#include <chrono>
#include <iostream>
#include <thread>

void foo()
{
    printf("hello from foo - %d \n", std::this_thread::get_id());
}

class callabele_class
{
public:
    void operator()() const 
    {
        std::cout << "Hello from class with function call operator - %d \n", std::this_thread::get_id();
    }
};

void run()
{
    std::thread thread1(foo);
    callabele_class obj;
    std::thread thread2(obj);

    thread1.join();
    thread2.join();

    std::thread thread3([] {
        printf("Hello from lambda - %d \n", std::this_thread::get_id());
    });

    thread3.join();

    printf("Hello from main - %d \n", std::this_thread::get_id());
}

void foo2() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main()
{

    std::thread t;
    std::cout << "before starting, joinable: " << std::boolalpha << t.joinable() << '\n';

    t =std::thread(foo2);
    std::cout << "after starting, joinable: " << t.joinable() << '\n';

    t.join();
    std::cout << "after joining, joinable: " << t.joinable() << '\n';
    return 0;
}