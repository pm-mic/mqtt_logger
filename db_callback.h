#pragma once

#include "mqtt_database.h"
#include "Imqtt_subscribe_callback.h"

class db_callback : public Imqtt_subscribe_callback
{
public: 
    db_callback(mqtt_database &db)
        : _db(db)
    {
    }
    
    void call(mqtt_message &message)
    {
        this->_db.store_message(message);
    }
private:
    mqtt_database &_db;
};