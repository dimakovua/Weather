// client.cpp
#include "client.hpp"

ClientLayer::Client::Client(const NetworkLayer::ContextPtr & context_ptr) : m_connection(new NetworkLayer::Network(context_ptr, {m_address, m_port})){
    
}

void ClientLayer::Client::setCity(const std::string &city_name){
    m_city = city_name;
}
void ClientLayer::Client::setToken(const std::string &token){
    m_token = token;
}
void ClientLayer::Client::setPort(const std::string & port){
    m_port = port;
    changeIPforNetwork();
}
void ClientLayer::Client::setAddress(const std::string & address){
    m_address = address;
    changeIPforNetwork();
}
void ClientLayer::Client::changeIPforNetwork(){
    m_connection->changeIP({m_address, m_port});
}
void ClientLayer::Client::process(){
    if(m_connection->start()){
        m_connection->send(m_city, m_token);
        std::string answer_json = m_connection->receive();
        std::cout << Parse_Json(answer_json);
    }
    else{
        std::cout << "Can't reach server!" << std::endl;
    }
}
std::string ClientLayer::Client::Parse_Json(std::string answer_in_json){
    try{
        std::stringstream jsonEncod(answer_in_json);
        boost::property_tree::ptree root;
        boost::property_tree::read_json(jsonEncod, root);
        try{
            if (!root.get<std::string>("message").empty()){
                return "Can't get weather in " + m_city + "\n";
            }
        }
        catch (...){}
        std::string answer_to_return  = "City: " + root.get<std::string>("name") + "\n" + "Temperature: " + root.get<std::string>("main.temp") + "°C\n" +
        "Wind's speed: " + root.get<std::string>("wind.speed") + " meter/sec\n" +
        "Wind's direction: " + root.get<std::string>("wind.deg") + "°\n";
        return answer_to_return;
    }
    catch(std::exception& e){
        std::cout << "Error! :(  " << e.what() << std::endl;
        return "";
    }
}
