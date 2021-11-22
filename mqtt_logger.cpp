// libraries
#include <iostream>
#include "mqtt/async_client.h"

// program files
#include "mqtt_logger_constants.h"
#include "mqtt_logger_config.h"
#include "mqtt_database.h"

int main(int argc, char *argv[])
{
    // open config file
    mqtt_logger_config config = mqtt_logger_config(Constants::config_filename);
    
    auto broker_ip = config.get_broker_ip();
    auto topics = config.get_topics();
    
    // open or create database
    mqtt_database db = mqtt_database(Constants::database_filename);
    
    // make mqtt connections
    
    
    // subscribe to topics
    
    
    // do logging
    
    // while this program is not finished...
    std::cout << "Logging..." << std::endl;
    
    while( 1 ) ;
    
	return 0;
}
