#include "application.hpp"

int main(int argc, char* argv[])
{
   ApplicationLayer::Application Weather(argc, argv);
   return Weather.exec();
}
