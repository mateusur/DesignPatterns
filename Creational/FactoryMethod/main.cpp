#include "NotificationFactories.hpp"

int main(){
    NotificationFactory* factory = nullptr;

    factory = new EmailNotificationFactory();
    factory -> notify("Hello World!");
    delete factory;

    factory = new SMSNotificationFactory();
    factory -> notify("Hello World!");
    delete factory;

    return 0;
}