#include "mqtt_handler_action_listener.h"
#include <iostream>

mqtt_handler_action_listener::mqtt_handler_action_listener(const std::string &name)
    : _name(name)
{
    
}

void mqtt_handler_action_listener::on_failure(const mqtt::token &tok)
{
    std::cout << this->_name << "failure";
    
    if( tok.get_message_id() != 0 )
    {
        std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    }
    
    std::cout << std::endl;
}

void mqtt_handler_action_listener::on_success(const mqtt::token &tok)
{
    std::cout << this->_name << " success";
    
    if( tok.get_message_id() != 0 )
        std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    
    auto top = tok.get_topics();
    if( top && !top->empty() )
        std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
    
    std::cout << std::endl;
}