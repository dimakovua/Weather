// networklayer.cpp
#include "network.hpp"

NetworkLayer::Network::Network(const ContextPtr& context_ptr, const IPAddress connectionIP) : m_connectionIP(connectionIP), m_context_ptr(context_ptr), m_error(), m_socket(*context_ptr)
{
    
}
void NetworkLayer::Network::changeIP(IPAddress connectionIP){
    m_connectionIP = connectionIP;
}
bool NetworkLayer::Network::start(){
    try{
        tcp::resolver resolver(*(m_context_ptr));
        auto result = resolver.resolve(m_connectionIP.host, m_connectionIP.port, m_error);
        if(!m_error){
            boost::asio::connect(m_socket, result);
        }
        return m_socket.is_open();
    }
    catch(...){
        //std::cout << "Connection refused! Check your port or host" << std::endl;
        return 0;
    }
}
void NetworkLayer::Network::send(const std::string & city_name, const std::string & token){
    std::string request_string = "/data/2.5/weather?q="+ city_name +"&appid=" + token + "&units=metric";
    boost::beast::http::request<boost::beast::http::string_body> req (boost::beast::http::verb::get, request_string, 11);
    req.set(boost::beast::http::field::host, m_connectionIP.host);
    req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    send(req);
}
void NetworkLayer::Network::send(const http::request<http::string_body> & request){
    boost::beast::http::write(m_socket, request);
}

std::string NetworkLayer::Network::receive(){
    return boost::beast::buffers_to_string(p_receive().body().data());
}
NetworkLayer::http::response<NetworkLayer::http::dynamic_body> NetworkLayer::Network::p_receive(){
    boost::beast::flat_buffer buffer;
    boost::beast::http::response<boost::beast::http::dynamic_body> res;
    boost::beast::http::read(m_socket, buffer, res);
    return res;
}
