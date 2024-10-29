#include "SMSNotification.hpp"
#include <iostream>

void SMSNotification::send(std::string_view notification_text) {
    std::cout << "Sending notification through SMS: " << notification_text << std::endl;
}