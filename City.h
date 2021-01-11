#ifndef CITY_HH
#define CITY_HH
#include "Graph.h"

class City {
    Graph graph;
    std::set<std::string> closed;

    public:
    std::set<std::string>& getClosed();
    std::set<std::string>& getCrossroads();
    std::set<std::string>& neighbours(const std::string& v);
    void addCrossroad(const std::string& v);
    void addStreet(const std::string& v1,const std::string& v2, const unsigned int& weight);
    void pathBetween(const std::string& v1, const std::string& v2);
    void halfTour(const std::string& v1);
    void fromOneToAllCrossroads(const std::string& v1);
    void shortestPaths(const std::string& v1, const std::string& v2);
    std::map<int, std::list<std::string>> aSinglePathPrint(std::set<std::string> alreadyVisited, const std::string& v1, const std::string& v2);
    void deadEnds();
    void eulerianCycle();
    void alternativeShortestPaths(std::set<std::string> closed, const std::string& v1, const std::string& v2);   
};

#endif