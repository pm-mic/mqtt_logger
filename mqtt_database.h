#pragma once

#include <string>
#include <sqlite3.h>

#include "mqtt_message.h"
#include "Imqtt_subscribe_callback.h"

class mqtt_database : public Imqtt_subscribe_callback
{
public:
    mqtt_database(std::string filename);
    
    void store_message(mqtt_message &message);
    
    void call(mqtt_message &message);
    
private:
    sqlite3 *_db;
};