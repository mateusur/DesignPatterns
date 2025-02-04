#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

struct Subject
{
    virtual void request() = 0;
    virtual ~Subject() = default;
};

struct RealSubject : Subject
{
    void request() override {
        cout << "Processing request" << endl;
    }
};

struct ProxySubject : Subject
{
    ProxySubject(){
        real = new RealSubject;
    }
    void request() override {
        cout << "Directing request to real subject" << endl;
        real->request();
    }
    ~ProxySubject(){
        delete real;
    }
private:
    RealSubject* real;
};

int main(){
    ProxySubject proxy;
    proxy.request();
    return 0;
}