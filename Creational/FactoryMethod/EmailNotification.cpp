#include "EmailNotification.hpp"
#include <iostream>

void EmailNotification::send(std::string_view notification_text) {
    std::cout << "Sending notification through email: " <<notification_text << std::endl;
}