#include "mqtt_handler_callback.h"

mqtt_handler_callback::mqtt_handler_callback
    (mqtt::async_client& cli, mqtt::connect_options& connOpts, std::atomic<bool> &connected) :
    _retries(0),
    _client(cli),
    _connect_options(connOpts),
    _subListener("Subscription"),
    _connected(connected)
{
}

void mqtt_handler_callback::reconnect()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try
    {
        this->_client.connect(this->_connect_options, nullptr, *this);
    }
    catch( const mqtt::exception& exc )
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        exit(1);
    }
}

// Re-connection failure
void mqtt_handler_callback::on_failure(const mqtt::token& tok)
{
    std::cout << "Connection attempt failed" << std::endl;
    if( ++this->_retries > N_RETRY_ATTEMPTS )
        exit(1);
    reconnect();
}

// (Re)connection success
// Either this or connected() can be used for callbacks.
void mqtt_handler_callback::on_success(const mqtt::token& tok) 
{
}

// (Re)connection success
void mqtt_handler_callback::connected(const std::string& cause)
{
    // subscribe all topics already known
    this->_client.subscribe(TOPIC, QOS, nullptr, this->_subListener);
}

// Callback for when the connection is lost.
// This will initiate the attempt to manually reconnect.
void mqtt_handler_callback::connection_lost(const std::string& cause)
{
    this->_connected = false;
    
    std::cout << "\nConnection lost" << std::endl;
    if( !cause.empty() )
        std::cout << "\tcause: " << cause << std::endl;

    std::cout << "Reconnecting..." << std::endl;
    this->_retries = 0;
    reconnect();
}

// Callback for when a message arrives.
void mqtt_handler_callback::message_arrived(mqtt::const_message_ptr msg)
{
    std::cout << "Message arrived" << std::endl;
    std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
    std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
}

void mqtt_handler_callback::delivery_complete(mqtt::delivery_token_ptr token) 
{
    
}