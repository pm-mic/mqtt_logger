#include "mqtt_handler.h" 

mqtt_handler::mqtt_handler(std::string broker_ip, std::string id, int port) :
    _subListener("subscription")
{
    // create client
    const std::string full_ip = "tcp://" + broker_ip + ":" + std::to_string(port);
    this->_client = std::make_unique<mqtt::async_client>(full_ip, id);
    
    // define options
    this->_options = std::make_unique<mqtt::connect_options>();
    
    // set callback
    this->_client->set_callback(*this);
    
    // connect
    try
    {
        this->_client->connect(*this->_options, nullptr, *this);
    }
    // to be improved
    catch( const mqtt::exception& exc )
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        throw std::runtime_error(exc.what());
    }
}

void mqtt_handler::subscribe(std::string topic, Imqtt_subscribe_callback *callback_class)
{    
    // if client is connected already, take care of subscription
    if( this->_client->is_connected() )
    {
        this->_client->subscribe(topic, this->_qos, nullptr, this->_subListener);
    }
    
    this->_subscribed_topics.insert({topic, callback_class});
}


void mqtt_handler::reconnect()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try
    {
        this->_client->connect(*this->_options, nullptr, *this);
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
    
    if( ++this->_retries > this->_max_retries )
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
    for( const auto& [key, value] : this->_subscribed_topics )
    {
        // subscribe all topics already known
        this->_client->subscribe(key, this->_qos, nullptr, this->_subListener);
    }
}

// Callback for when the connection is lost.
// This will initiate the attempt to manually reconnect.
void mqtt_handler::connection_lost(const std::string& cause)
{
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
    
    // call the corresponding callback
    auto &cb = this->_subscribed_topics[msg->get_topic()];
    
    mqtt_message context(msg->get_topic(), msg->get_payload());
    
    cb->call(context);
}

void mqtt_handler::delivery_complete(mqtt::delivery_token_ptr token) 
{
    
}