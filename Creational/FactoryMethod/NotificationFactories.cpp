#include "NotificationFactories.hpp"
#include "EmailNotification.hpp"
#include "SMSNotification.hpp"

void NotificationFactory::notify(const std::string& message){
    Notification* notification = createNotification();
    notification -> send(message);
    delete notification;
}

Notification* EmailNotificationFactory::createNotification() {
    return new EmailNotification();
}

Notification* SMSNotificationFactory::createNotification(){
    return new SMSNotification();
}