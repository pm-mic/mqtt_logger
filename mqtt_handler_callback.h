#pragma once

#include <atomic>

#include "mqtt/async_client.h"
#include "mqtt_handler_action_listener.h"

// temporary constants

const int	QOS = 1;
const int	N_RETRY_ATTEMPTS = 5;

class mqtt_handler_callback : 
    public virtual mqtt::callback, 
    public virtual mqtt::iaction_listener
{
public:
    mqtt_handler_callback(
        mqtt::async_client &cli, mqtt::connect_options &connOpts, std::atomic<bool> &connected);
private:
    // retry counter
    int _retries;
    mqtt::async_client &_client;
    // connection options for reconnect attempts
    mqtt::connect_options &_connect_options;
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