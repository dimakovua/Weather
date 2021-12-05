// application.cpp
#include "application.hpp"

ApplicationLayer::Application::Application(int argc, char **argv) : argc(argc), argv(argv), m_options("Options"){}
void ApplicationLayer::Application::set_options(){
    m_options.add_options()
        ("help,h", "Show help")
        ("city,c", boost::program_options::value<std::string>(), "Enter city (If the city name is divided into several words - use _ instead of space)")
        ("token,t", boost::program_options::value<std::string>(), "Enter token")
        ("address,a", boost::program_options::value<std::string>(), "Enter address (host)")
        ("port,p", boost::program_options::value<std::string>(), "Enter port");
}

int ApplicationLayer::Application::parser(){
    boost::program_options::variables_map map;
    ClientLayer::Client c(std::make_shared<boost::asio::io_context>());
    try{
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, m_options), map);
        if(map.count("help") || argc == 1){
            std::cout << m_options <<std::endl;
        }
        if (map.count("city")){
            c.setCity(map["city"].as<std::string>());
        }
        if (map.count("token")){
            c.setToken(map["token"].as<std::string>());
        }
        if (map.count("port")){
            c.setPort(map["port"].as<std::string>());
        }
        if (map.count("address")){
            c.setAddress(map["address"].as<std::string>());
        }
    }
    catch (std::exception& ex){
        std::cout << "Error while parsing: " << ex.what() <<std::endl;
        std::cout << m_options << std::endl;
        return 1;
    }
    catch(...){
        std::cout << "Unknown error while parsing: " << std::endl;
        std::cout << m_options << std::endl;
        return 1;
    }
    c.process();
    return 0;
}
int ApplicationLayer::Application::exec(){
    set_options();
    return parser();
}
