#include "Graph.h"
#include "City.h"
#include "UserInterface.h"
#include <fstream>

void insertIntoCity(City &city, std::string str)
{
    std::string word = "";
    std::string mainCrossroad = "";
    std::string secondaryCrossroad = "";
    int counter = 0;
    int size = str.length();

    for (auto x : str)
    {
        if (x == ' ')
        {
            if (mainCrossroad == "")
            {
                mainCrossroad = word;
                word = "";
                counter++;
                continue;
            }

            if (secondaryCrossroad == "" && mainCrossroad != "")
            {
                secondaryCrossroad = word;
                word = "";
                counter++;
                continue;
            }

            if (secondaryCrossroad != "" && mainCrossroad != "")
            {
                city.addStreet(mainCrossroad, secondaryCrossroad, std::stoi(word));
                secondaryCrossroad = "";
                word = "";
            }

            counter++;
        }
        else
        {
            word = word + x;
            counter++;
            if(counter == size){
                city.addStreet(mainCrossroad, secondaryCrossroad, std::stoi(word));
            }
        }
    }
}

int main()
{

    City graph;

    std::ifstream infile;

    infile.open("input.txt");

    if (infile.fail())
    {
        std::cout << "File failed to open!" << std::endl;
        return 0;
    }
    else
    {
        std::string s;
        while (getline(infile, s))
        {
            insertIntoCity(graph, s);
        }

        std::set<std::string> closed;

        std::cout << std::endl;

        UserInterface ui(graph);

        ui.start();

        infile.close();
    }

    return 0;
}