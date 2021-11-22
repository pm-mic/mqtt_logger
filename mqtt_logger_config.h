#pragma once

#include <vector>
#include <string>

typedef std::vector<std::string> topics_array;

class mqtt_logger_config
{
public:
    mqtt_logger_config(std::string filename);
    
    // gets the broker ip address
    std::string get_broker_ip(void);
        
    // gets all topics in a vector
    topics_array get_topics(void);
    
    // get id
    std::string get_id(void);
    
private:
    bool _initialized;
    
    void _load_config(void);
     
    std::string _filename;
    const std::string _broker_ip_label = "broker_ip";
    const std::string _topics_label = "topics";
    const std::string _id_label = "id";
    
    std::string _id;
    std::string _broker_ip;
    std::vector<std::string> _topics;    
};