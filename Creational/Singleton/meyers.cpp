#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using std::string;

class Singleton
{
private:
    Singleton(string val) : value(val) {};
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;
public:
    string value;
    static Singleton& getInstance(string value) {
        static Singleton instance(value);
        return instance;
    }
};

void threadOne(string value){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << Singleton::getInstance(value).value << std::endl;
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
