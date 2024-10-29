#pragma once
#include "Notification.hpp"

class NotificationFactory {
public:
    virtual Notification* createNotification() = 0;
    void notify(const std::string& message);
    virtual ~NotificationFactory(){};
};

class EmailNotificationFactory : public NotificationFactory {
public:
    Notification* createNotification() override;
};

class SMSNotificationFactory : public NotificationFactory {
public:
    Notification* createNotification() override;
};