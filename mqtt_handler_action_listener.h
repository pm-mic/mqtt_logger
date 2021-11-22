#pragma once

#include "mqtt/async_client.h"

// Callbacks for the success or failures of requested actions.
// This could be used to initiate further action, but here we just log the
// results to the console.

class mqtt_handler_action_listener : public virtual mqtt::iaction_listener
{
public:
    mqtt_handler_action_listener(const std::string &name);
    
private:
    void on_failure(const mqtt::token &tok) override;
    void on_success(const mqtt::token &tok) override;
    
    const std::string &_name;
};


