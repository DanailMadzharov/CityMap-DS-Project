#ifndef UI_HH
#define UI_HH
#include "City.h"

class UserInterface
{
    City city;
    std::set<std::string> closed;
    void interactive();

    public:
    UserInterface(City _city);
    void start();
    void printMenu();
};

#endif