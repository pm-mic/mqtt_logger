#pragma once

#include <string>
#include "mqtt_message.h"
#include <sqlite3.h>

class mqtt_database
{
public:
    mqtt_database(std::string filename);
    
    void store_message(mqtt_message &message);
    
private:
    sqlite3 *_db;
};