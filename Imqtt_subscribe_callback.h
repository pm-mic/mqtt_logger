#pragma once

#include "mqtt_message.h"

class Imqtt_subscribe_callback
{
public:
    virtual void call(mqtt_message &message) = 0; 
};