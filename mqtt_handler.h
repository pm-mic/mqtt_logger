#pragma once

#include <atomic>

#include "mqtt/async_client.h"
#include "mqtt_message.h"
#include "mqtt_handler_action_listener.h"

// signature for callback functions of received messages
typedef void(*mqtt_cb_t)(mqtt_message &message);

class mqtt_handler : 
    public virtual mqtt::callback, 
    public virtual mqtt::iaction_listener
{
public: 
    mqtt_handler(std::string broker_ip, std::string id, int port = 1883);

    void subscribe(std::string topic, mqtt_cb_t function);        
private:
    std::unique_ptr<mqtt::async_client> _client;
    std::unique_ptr<mqtt::connect_options> _options;   
    
    std::map<std::string, mqtt_cb_t> _subscribed_topics;
    
    // performed amount of retries
    int _retries = 0;
    // An action listener to display the result of actions.
    mqtt_handler_action_listener _subListener;
    
    void reconnect(void);
    void on_failure(const mqtt::token& tok) override;
    void on_success(const mqtt::token& tok) override;
    void connected(const std::string& cause) override;
    void connection_lost(const std::string& cause) override;
    void message_arrived(mqtt::const_message_ptr msg) override;
    void delivery_complete(mqtt::delivery_token_ptr token) override;
};