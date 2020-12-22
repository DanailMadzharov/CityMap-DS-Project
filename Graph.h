#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <set>
#include <list>
#include <exception>
#include <vector>
#include <string>

class Graph {
    std::set<std::string> vertices;
    std::map<std::string, std::set<std::string>> neighs;
    std::map<std::pair<std::string, std::string>, int> weights;

    public:

    std::set<std::string>& getVertices();
    void addVertex(const std::string& v);
    void addEdge(const std::string& v1,const std::string& v2, const unsigned int& weight);
    bool hasVetrex(const std::string& v) const;
    bool hasEdge(const std::string& v1, const std::string& v2) const;
    int getEdge(const std::string& v1,const std::string& v2);
    std::set<std::string>& neighbours(const std::string& v);
    void printAllNeighbours();
    void printVertices(std::string& v);
    bool pathBetween(const std::string& v1, const std::string& v2);
    bool halfTour(const std::string& v1);
    bool fromOneToAllCrossroads(const std::string& v1);
    std::map<int, std::list<std::string>> shortestPaths(std::set<std::string> alreadyVisited, const std::string& v1, const std::string& v2);
    std::set<std::string> deadEnds();
    std::list<std::string> eulerianCycle();

    private:
    void shortestPathsHelper(const std::string& v1, const std::string& v2, std::set<std::string>& alreadyVisited,
                             std::list<std::string>& paths, std::map<int, std::list<std::string>>& pathsAndLengths);
    int inDegrees(std::string& v);
    void eulerianCycleHelper(std::string& v1, std::map<std::string, std::set<std::string>>& neighsCopy,
     std::list<std::string>& path);
     bool isThereEulerianCycle();
};

 #endif //GRAPH_HH