#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using std::string;

class Singleton
{
private:
    static Singleton* instance;
    static std::once_flag initSingletonFlag;
    Singleton(string val) : value(val) {};
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;
    static void initSingleton(string value){
        instance = new Singleton(value);
    }
public:
    string value;
    static Singleton* getInstance(string value) {
        std::call_once(initSingletonFlag,initSingleton,value);
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
std::once_flag Singleton::initSingletonFlag;


void threadOne(string value){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << Singleton::getInstance(value)->value << std::endl;
}

int main() {
    std::thread t1(threadOne,"One");
    std::thread t2(threadOne,"Two");
    std::thread t3(threadOne,"Three");

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
