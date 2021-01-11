#include "UserInterface.h"
#include <string>
#include <chrono>
#include <thread>

UserInterface::UserInterface(City _city) : city(_city) {}

void UserInterface::start()
{
    std::cout << "Hello and welcome!" << std::endl;
    std::cout << std::endl;
    std::cout << "Would you like to go into interactive mode? Type y/n" << std::endl;
    std::string answer;
    do
    {
        std::cout << "choice: ";
        std::cin >> answer;
    } while (answer != "y" && answer != "n");

    if (answer == "y")
    {
        std::cout << std::endl;
        interactive();
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Goodbye! Feel free to use the app in main.cpp!";
    }
}

void UserInterface::interactive()
{

    std::string currentLocation = *(city.getCrossroads().begin());
    std::string word1;
    std::string word2;

    std::cout<<std::endl<<std::endl<<"Current location: "<<currentLocation<<std::endl<<std::endl;

    while (true)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(x));


        printMenu();
        std::cout << std::endl;

        std::cin>>word1;

        if (word1 == "location")
        {
            std::cout<<std::endl;
            std::cout << "Current location: " << currentLocation << std::endl;
        }
        else if (word1 == "neighbours")
        {
            std::cout<<std::endl << "Neighbours of " << currentLocation << " are: " << std::endl;

            std::set<std::string> neighs = city.neighbours(currentLocation);

            std::cout << std::endl;

            int counter = 1;

            for (auto const &elem : neighs)
            {
                std::cout <<counter<<". "<< elem << std::endl;
                counter++;
            }
        }
        else if (word1 == "tour")
        {
            city.eulerianCycle();
        }
        else if (word1 == "quit")
        {
            std::cout<<"Quitting..."<<std::endl;
            return;
        }
        else if (word1 == "closed")
        {
            int counter = 1;

            std::cout<<"The following crossroads are closed: "<<std::endl;
         
            for(auto const& element : city.getClosed()){
                std::cout<<counter<<". "<<element<<std::endl;
                counter++;
            }

            std::cout<<std::endl;
        }
        else if (word1 == "change" || word1 == "move" || word1 == "close" || word1 == "open" || word1 == "dead")
        {
            std::getline(std::cin, word2);
            
            word2.erase(word2.begin());

            if(word2 == "ends") {
                city.deadEnds();
            }
            
            else {
            if (city.getCrossroads().count(word2) != 0)
            {
                if (word1 == "change")
                {
                    std::cout<<std::endl;
                    currentLocation = word2;
                    std::cout<<std::endl<<"Location has been changed to "<<word2<<std::endl;
                }
                else if (word1 == "move")
                {
                    std::cout<<std::endl;
                    std::map<int, std::list<std::string>> allPaths = city.aSinglePathPrint(city.getClosed(), currentLocation, word2);
                    if(allPaths.empty()){
                        std::cout<<std::endl<<"There is no possible path to this location!"<<std::endl;
                    } else {
                        currentLocation = word2;
                    }
                    std::cout<<std::endl;
                }
                else if (word1 == "close")
                {
                    city.getClosed().insert(word2);
                    std::cout<<std::endl;
                }
                else if (word1 == "open")
                {
                    city.getClosed().erase(word2);
                    std::cout<<std::endl;
                }
                } else {
                    std::cout<<std::endl<<std::endl<<"This crossroad does not exist!"<<std::endl;
                    std::cout<<std::endl;
                }
            }
        }
    }
}

void UserInterface::printMenu()
{
    std::cout<<std::endl;
    std::cout << "You have the following commands: " << std::endl
              << std::endl;
    std::cout << "\t 1. 'location' - shows you the current location" << std::endl;
    std::cout << "\t 2. 'change @' - changes the current location to @ (if it exists)" << std::endl;
    std::cout << "\t 3. 'neighbours' - shows you the adjecent crossroad to the current one" << std::endl;
    std::cout << "\t 4. 'move @' - move to a location from the current location (if a path and the crossroad exist)" << std::endl;
    std::cout << "\t 5. 'close @' - adds @ to the list of closed crossroads" << std::endl;
    std::cout << "\t 6. 'open @' - removes @ from the list of closed crossroads" << std::endl;
    std::cout << "\t 7. 'tour' - a full tour of the city (if possible)" << std::endl;
    std::cout << "\t 8. 'closed' - a full list of the closed crossroads" << std::endl;
    std::cout << "\t 9. 'dead ends' - returns a list of all dead ends in the city" << std::endl;
    std::cout << "\t10. 'quit' - quits the program" << std::endl;
}