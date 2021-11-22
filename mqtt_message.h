#pragma once

#include <string>
#include <ctime>

class mqtt_message
{
public:
    mqtt_message(std::string topic, std::string payload) :
        topic(topic),
        payload(payload),
        timestamp(std::time(nullptr))
    {
    }
    
    const std::string topic;
    const std::string payload;
    const std::time_t timestamp;
private:
    
};