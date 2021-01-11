#include "City.h"

void City::addCrossroad(const std::string &v)
{
    try
    {
        graph.addVertex(v);
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void City::addStreet(const std::string &v1, const std::string &v2, const unsigned int &weight)
{
    try
    {
        graph.addEdge(v1, v2, weight);
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void City::pathBetween(const std::string &v1, const std::string &v2)
{
    try
    {
        if (graph.pathBetween(v1, v2))
        {
            std::cout << "There is a path!" << std::endl;
        }
        else
        {
            std::cout << "There is no path!" << std::endl;
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void City::halfTour(const std::string &v1)
{
    try
    {
        if (graph.halfTour(v1))
        {
            std::cout << "There is a half tour!" << std::endl;
        }
        else
        {
            std::cout << "There is not half tour!" << std::endl;
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void City::fromOneToAllCrossroads(const std::string &v1)
{
    try
    {
        if (graph.fromOneToAllCrossroads(v1))
        {
            std::cout << "Yes, you can reach all crossroads from this vertex!" << std::endl;
        }
        else
        {
            std::cout << "No, you cannot reach them all!" << std::endl;
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void City::shortestPaths(const std::string &v1, const std::string &v2)
{
    try
    {
        std::set<std::string> alreadyVisited;
        std::map<int, std::list<std::string>> pathsAndLengths = graph.shortestPaths(alreadyVisited, v1, v2);

        int counter = 0;

        for (auto const &elem : pathsAndLengths)
        {
            if (counter == 3)
            {
                break;
            }
            for (auto const &str : elem.second)
            {
                if (str == elem.second.back())
                {
                    std::cout << str;
                    break;
                }
                std::cout << str << " -> ";
            }
            std::cout << " : " << elem.first << " m" << std::endl;

            counter++;
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void City::deadEnds()
{
    std::set<std::string> deadEnds = graph.deadEnds();
    if (deadEnds.empty())
    {
        std::cout << "No dead end streets!" << std::endl;
        return;
    }

    std::cout << "Streets that lead to dead ends: " << std::endl;
    std::cout << std::endl;

    for (auto const &start : graph.getVertices())
    {
        for (auto const &end : deadEnds)
        {
            if (graph.hasEdge(start, end))
            {
                std::cout << start << " -> " << end << std::endl;
            }
        }
    }
}

void City::eulerianCycle()
{
    std::list<std::string> cycle = graph.eulerianCycle();

    if (cycle.empty())
    {
        std::cout << "There is no possible full tour!" << std::endl;
        return;
    }

    int counter = 0;
    int stop = cycle.size();

    for (auto const &elem : cycle)
    {
        if (counter == stop - 1)
        {
            std::cout << elem << std::endl;
            break;
        }
        std::cout << elem << " -> ";
        counter++;
    }
}

void City::alternativeShortestPaths(std::set<std::string> closed, const std::string &v1, const std::string &v2)
{
    try
    {
        std::map<int, std::list<std::string>> pathsAndLengths = graph.shortestPaths(closed, v1, v2);

        if (pathsAndLengths.empty())
        {
            std::cout << "There are no alternative paths!" << std::endl;
            return;
        }

        int counter = 0;

        for (auto const &elem : pathsAndLengths)
        {
            if (counter == 3)
            {
                break;
            }
            for (auto const &str : elem.second)
            {
                if (str == elem.second.back())
                {
                    std::cout << str;
                    break;
                }
                std::cout << str << " -> ";
            }
            std::cout << " : " << elem.first << " m" << std::endl;

            counter++;
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }
}

std::set<std::string> &City::getCrossroads()
{
    return graph.getVertices();
}

std::set<std::string> &City::neighbours(const std::string &v)
{
    return graph.neighbours(v);
}

std::map<int, std::list<std::string>> City::aSinglePathPrint(std::set<std::string> alreadyVisited, const std::string &v1,
                                                        const std::string &v2)
{
    std::map<int, std::list<std::string>> allPaths = graph.shortestPaths(alreadyVisited, v1, v2);

    int counter = 0;

    for (auto const &elem : allPaths)
    {
        if (counter == 1)
        {
            break;
        }

        for (auto const &str : elem.second)
        {
            if (str == elem.second.back())
            {
                std::cout << str;
                std::cout << " | length "<<elem.first;
                break;
            }
            std::cout << str << " -> ";
        }

        counter++;

        return allPaths;
    }
}

std::set<std::string>& City::getClosed(){
    return this->closed;
}
