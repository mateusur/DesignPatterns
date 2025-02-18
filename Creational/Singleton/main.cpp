#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using std::string;

class Singleton
{
private:
    static Singleton* instance;
    static std::mutex mtx;
    Singleton(string val) : value(val) {};
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;
public:
    string value;
    static Singleton* getInstance(string value) {
        std::lock_guard<std::mutex> lock(mtx);
        if(!instance){
            instance = new Singleton(value);
        }
        return instance;
    }
};

void threadOne(string value){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* instance = Singleton::getInstance(value);
    std::cout << instance->value << std::endl;
}
std::mutex Singleton::mtx;
Singleton* Singleton::instance = nullptr;

int main() {
    std::thread t1(threadOne,"One");
    std::thread t2(threadOne,"Two");
    std::thread t3(threadOne,"Three");

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
