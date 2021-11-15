// libraries
#include <iostream>

// program files
#include "mqtt_logger_constants.h"
#include "mqtt_logger_settings.h"

Settings load_config(std::string filename);

int main(int argc, char *argv[])
{
    // open config file
    Settings program_settings;
    
    program_settings = load_config(Constants::config_filename);
    
    // open or create database
    
    
    // subscribe to topics
    
    
    // do logging
    
    // while this program is not finished...
    std::cout << "Logging..." << std::endl;
    
    while( 1 ) ;
    
	return 0;
}

Settings load_config(std::string filename)
{

    
    Settings return_value;
    
    
    
    return return_value;
}