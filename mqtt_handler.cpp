#include "mqtt_handler.h" 

mqtt_handler::mqtt_handler(std::string broker_ip, std::string id, int port)
{
    // create client
    const std::string full_ip = "tcp://" + broker_ip + ":" + std::to_string(port);
    this->_client = std::make_unique<mqtt::async_client>(full_ip, id);
    
    // define options
    this->_options = std::make_unique<mqtt::connect_options>();
    
    // create callback class
    
}

void mqtt_handler::subscribe(std::string topic, mqtt_cb_t function)
{    
    // if client is connected already, take care of subscription
    if( this->_client->is_connected() )
    {
        this->_client->subscribe()
    }
    
    this->_subscribed_topics.insert({topic, function});
}


void mqtt_handler::reconnect()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try
    {
        this->_client.connect(this->_connect_options, nullptr, *this);
    }
    catch( const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        exit(1);
    }
}

// Re-connection failure
void mqtt_handler::on_failure(const mqtt::token& tok)
{
    std::cout << "Connection attempt failed" << std::endl;
    if( ++this->_retries > N_RETRY_ATTEMPTS )
        exit(1);
    reconnect();
}

// (Re)connection success
// Either this or connected() can be used for callbacks.
void mqtt_handler::on_success(const mqtt::token& tok) 
{
}

// (Re)connection success
void mqtt_handler::connected(const std::string& cause)
{
    // subscribe all topics already known
    this->_client.subscribe(TOPIC, QOS, nullptr, this->_subListener);
}

// Callback for when the connection is lost.
// This will initiate the attempt to manually reconnect.
void mqtt_handler::connection_lost(const std::string& cause)
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
void mqtt_handler::message_arrived(mqtt::const_message_ptr msg)
{
    std::cout << "Message arrived" << std::endl;
    std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
    std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
}

void mqtt_handler::delivery_complete(mqtt::delivery_token_ptr token) 
{
    
}