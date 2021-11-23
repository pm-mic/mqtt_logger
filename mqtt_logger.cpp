// libraries
#include <iostream>

// program files
#include "mqtt_logger_constants.h"
#include "mqtt_logger_config.h"
#include "mqtt_database.h"
#include "mqtt_handler.h"
#include "db_callback.h"

int main(int argc, char *argv[])
{
    // open config file
    mqtt_logger_config config = mqtt_logger_config(Constants::config_filename);
    
    auto broker_ip = config.get_broker_ip();
    auto topics = config.get_topics();
    auto id = config.get_id();
    
    // open or create database
    mqtt_database db(Constants::database_filename);
    db_callback db_cb(db);
    
    // make mqtt connections
    mqtt_handler handler(broker_ip, id);
    
    // subscribe to topics
    for( auto const &topic : topics )
    {
        handler.subscribe(topic, &db_cb);
    }
    
    // do logging
    
    // while this program is not finished...
    std::cout << "Logging..." << std::endl;

    while( 1 ) ;
    
    std::cout << "Quitting..." << std::endl;
    
	return 0;
}
