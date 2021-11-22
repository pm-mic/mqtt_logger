#include "mqtt_logger_config.h"
#include <libconfig.h++>

mqtt_logger_config::mqtt_logger_config(std::string filename) :
    _initialized(false),
    _filename(filename)
{
}

std::string mqtt_logger_config::get_broker_ip(void)
{
    if( !this->_initialized )
    {
        // load file
        this->_load_config();
    }
    
    return this->_broker_ip;
}
    
topics_array mqtt_logger_config::get_topics(void)
{
    if( !this->_initialized )
    {
        // load file
        this->_load_config();
    }
    
    return this->_topics;
}

std::string mqtt_logger_config::get_id(void)
{
    if( !this->_initialized )
    {
        // load file
        this->_load_config();
    }
    
    return this->_id;
}

void mqtt_logger_config::_load_config(void)
{
    libconfig::Config cfg;
    
    cfg.readFile(this->_filename.c_str());
    
    // get ip from file
    this->_broker_ip = cfg.lookup(this->_broker_ip_label).c_str();

    // get topics from file
    libconfig::Setting &topics = cfg.lookup(this->_topics_label);
        
    for( int i = 0; i < topics.getLength(); i++ )
    {
        this->_topics.push_back(topics[i]);
    }
    
    // get id
    this->_id = cfg.lookup(this->_id_label).c_str();
    
    this->_initialized = true;
}