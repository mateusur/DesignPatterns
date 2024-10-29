#pragma once
#include <string_view>

class Notification {
public:
    virtual void send(std::string_view notification_text) = 0;
    ~Notification(){};
};