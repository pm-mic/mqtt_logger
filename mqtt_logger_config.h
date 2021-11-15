#pragma once

#include <vector>
#include <string>

typedef std::vector<std::string> topics_array;

enum class CONFIG_ERROR
{
    NONE,
    FILE_ERROR,
    PARSE_ERROR, 
    IP_ERROR, 
    TOPICS_ERROR
};

class mqtt_logger_config
{
public:
    mqtt_logger_config(std::string filename);
    
    // gets the broker ip address in a 4 byte array
    CONFIG_ERROR get_broker_ip(char *address);
    
    // gets all topics in a vector
    CONFIG_ERROR get_topics(topics_array *config_toppics);
    
private:
    bool _initialized;
    
    CONFIG_ERROR _load_config();
    
    std::string _filename;
    const std::string broker_ip_label = "broker_ip";
    const std::string topics_label = "topics";
    
    char _broker_ip[4];
    std::vector<std::string> _topics;    
};