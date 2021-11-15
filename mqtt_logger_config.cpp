#include "mqtt_logger_config.h"
#include <libconfig.h++>

mqtt_logger_config::mqtt_logger_config(std::string filename) :
    _initialized(false),
    _filename(filename)
{
}

CONFIG_ERROR mqtt_logger_config::get_broker_ip(char *address)
{
    if( !this->_initialized )
    {
        auto config_load_result = this->_load_config();
        
        if( config_load_result != CONFIG_ERROR::NONE )
        {
            return config_load_result;
        }
        else
        {
            
        }
    }
}
    
// gets all topics in a vector
CONFIG_ERROR mqtt_logger_config::get_topics(topics_array *config_toppics)
{
    
}