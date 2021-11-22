// libraries
#include <iostream>

// program files
#include "mqtt_logger_constants.h"
#include "mqtt_logger_config.h"
#include "mqtt_database.h"
#include "mqtt_handler.h"

int main(int argc, char *argv[])
{
    // open config file
    mqtt_logger_config config = mqtt_logger_config(Constants::config_filename);
    
    auto broker_ip = config.get_broker_ip();
    auto topics = config.get_topics();
    auto id = config.get_id();
    
    // open or create database
    mqtt_database db = mqtt_database(Constants::database_filename);
    
    // make mqtt connections
    mqtt_handler handler(broker_ip, id);
    
    // subscribe to topics
    for( auto const &topic : topics )
    {
        handler.subscribe(topic, &db);
    }
    
    // do logging
    
    // while this program is not finished...
    std::cout << "Logging..." << std::endl;
    
    while( 1 ) ;
    
	return 0;
}
