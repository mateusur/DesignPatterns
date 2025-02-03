#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

struct Button {
    virtual void clicked() = 0;
};

struct LinuxButton : Button
{
    void clicked() override {
        cout << "Linux click" << endl;
    }
};

struct WindowsButton : Button
{
    void clicked() override {
        cout << "Windows clack" << endl;
    }
};

struct Menu {
    virtual void dropdown() = 0;
    virtual ~Menu() = default;
};

struct LinuxMenu : Menu
{
    void dropdown() override {
        cout << "Linux dropdown menu" << endl;
    }
};
struct WindowsMenu : Menu
{
    void dropdown() override {
        cout << "Windows dropdown menu" << endl;
    }
};

struct Factory {
    virtual unique_ptr<Button> create_button() = 0;
    virtual unique_ptr<Menu> create_menu() = 0;
};

struct LinuxFactory : Factory
{
    unique_ptr<Button> create_button() override {
        return std::make_unique<LinuxButton>();
    }
    unique_ptr<Menu> create_menu() override {
        return std::make_unique<LinuxMenu>();
    }
};

struct WindowsFactory : Factory
{
    unique_ptr<Button> create_button() override {
        return std::make_unique<WindowsButton>();
    }
    unique_ptr<Menu> create_menu() override {
        return std::make_unique<WindowsMenu>();
    }
};

struct Client
{
    Client(unique_ptr<Factory> f) : factory(std::move(f)){}
    void click_button(){
        factory->create_button()->clicked();
    }
    void drop_menu(){
        factory->create_menu()->dropdown();
    }
private:
    unique_ptr<Factory> factory;
};

int main() {
    unique_ptr<Factory> f = std::make_unique<LinuxFactory>();
    unique_ptr<Client> c = std::make_unique<Client>(std::move(f));
    c->click_button();
    c->drop_menu();
    return 0;
}
