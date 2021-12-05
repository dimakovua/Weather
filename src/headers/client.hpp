#ifndef CLIENT_H
#define CLIENT_H
#include "network.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace ClientLayer
{
    using tcp = NetworkLayer::tcp;

    class Client
    {
    public:
        /**
         * @brief Ctor
         * @param context_ptr - smart pointer to io_context
         * @param host - server address
         * @param port - server port
         * */
        Client(const NetworkLayer::ContextPtr & context_ptr);

        /**
         * @brief Main function that connections to server, sends request and shows result
         * */
        void process();

        void setCity(const std::string & city_name);
        void setToken(const std::string & token);
        void setPort(const std::string & port);
        void setAddress(const std::string& address);
        void changeIPforNetwork();
    private:
        std::string Parse_Json(std::string answer_in_json);
        std::string m_city = "";
        std::string m_token = "8915429fcf6a68275f7c20caab444827";
        std::string m_port = "80";
        std::string m_address = "api.openweathermap.org";
        std::shared_ptr<NetworkLayer::Network> m_connection;
    };
}

#endif