#include "Graph.h"
#include <queue>
#include <stack>
#include <vector>

void Graph::addVertex(const std::string &v)
{
    if (vertices.count(v) == 1)
    {
        throw std::invalid_argument("Crossroad already excists!");
    }
    vertices.insert(v);
    neighs[v];
}

void Graph::addEdge(const std::string &v1, const std::string &v2, const unsigned int &weight)
{
    if (neighs[v1].count(v2) == 1)
    {
        throw std::invalid_argument("This street already exists!");
    }
    if (v1 == v2)
    {
        throw std::invalid_argument("A Crossroad can not have a street to itself!");
    }
    vertices.insert(v1);
    vertices.insert(v2);
    neighs[v1].insert(v2);
    weights[std::make_pair(v1, v2)] = weight;
}

bool Graph::hasVetrex(const std::string &v) const
{
    return vertices.count(v) == 1;
}

bool Graph::hasEdge(const std::string &v1, const std::string &v2) const
{
    return vertices.count(v1) == 1 && vertices.count(v2) == 1 && neighs.at(v1).count(v2) == 1;
}

int Graph::getEdge(const std::string &v1, const std::string &v2)
{
    if (!hasEdge(v1, v2))
    {
        throw std::invalid_argument("No edge present!");
    }

    return weights[std::make_pair(v1, v2)];
}

std::set<std::string> &Graph::neighbours(const std::string &v)
{
    if (!hasVetrex(v))
    {
        throw std::invalid_argument("No such crossroad");
    }

    return neighs[v];
}

void Graph::printAllNeighbours()
{
    for (auto s : vertices)
    {
        std::cout << s << " - ";
        printVertices(s);
    }
}

void Graph::printVertices(std::string &v)
{
    if (neighs[v].empty())
    {
        std::cout << " NULL";
    }
    else
    {
        for (auto s : neighs[v])
        {
            std::cout << s << ", ";
        }
    }
    std::cout << std::endl;
}

bool Graph::pathBetween(const std::string &v1, const std::string &v2)
{
    std::set<std::string> alreadyVisited;
    std::queue<std::string> ToVisit;

    if (vertices.count(v1) == 0 || vertices.count(v2) == 0)
    {
        throw std::invalid_argument("One or both vertexes are not present!");
    }

    alreadyVisited.insert(v1);
    for (auto const &elem : neighs[v1])
    {
        ToVisit.push(elem);
    }

    while (!ToVisit.empty())
    {
        if (ToVisit.front() == v2)
        {

            return true;
        }
        else
        {
            if (alreadyVisited.count(ToVisit.front()) == 1)
            {
                ToVisit.pop();
                continue;
            }
            alreadyVisited.insert(ToVisit.front());
            for (auto elem : neighs[ToVisit.front()])
            {
                ToVisit.push(elem);
            }
            ToVisit.pop();
        }
    }

    return false;
}

bool Graph::halfTour(const std::string &v1)
{

    std::set<std::string> alreadyVisited;
    std::queue<std::string> ToVisit;

    if (vertices.count(v1) == 0)
    {
        throw std::invalid_argument("No such vertex!");
    }

    for (auto elem : neighs[v1])
    {
        ToVisit.push(elem);
    }

    while (!ToVisit.empty())
    {

        if (ToVisit.front() == v1)
        {

            return true;
        }
        else
        {
            if (alreadyVisited.count(ToVisit.front()) == 1)
            {
                ToVisit.pop();
                continue;
            }
            alreadyVisited.insert(ToVisit.front());
            for (auto elem : neighs[ToVisit.front()])
            {
                ToVisit.push(elem);
            }
            ToVisit.pop();
        }
    }

    return false;
}

bool Graph::fromOneToAllCrossroads(const std::string &v1)
{
    std::set<std::string> alreadyVisited;
    std::list<std::string> ToVisit;

    if (vertices.count(v1) == 0)
    {
        throw std::invalid_argument("No such crossroad");
    }

    alreadyVisited.insert(v1);
    for (auto elem : neighs[v1])
    {
        ToVisit.push_front(elem);
    }

    while (!ToVisit.empty())
    {
        if (alreadyVisited.count(ToVisit.front()) == 1)
        {
            ToVisit.pop_front();
            continue;
        }

        for (auto elem : neighs[ToVisit.front()])
        {
            ToVisit.push_back(elem);
        }

        alreadyVisited.insert(ToVisit.front());
        ToVisit.pop_front();
    }

    return (vertices.size() == alreadyVisited.size());
}

std::map<int, std::list<std::string>> Graph::shortestPaths(std::set<std::string> alreadyVisited, const std::string &v1, const std::string &v2)
{

    if (!hasVetrex(v1) || !hasVetrex(v2))
    {
        throw std::invalid_argument("One or more vertexes are not from the graph!");
    }

    std::list<std::string> paths;
    std::map<int, std::list<std::string>> pathsAndLengths;

    paths.push_back(v1);

    shortestPathsHelper(v1, v2, alreadyVisited, paths, pathsAndLengths);

    return pathsAndLengths;
}

void Graph::shortestPathsHelper(const std::string &v1, const std::string &v2, std::set<std::string> &alreadyVisited,
                                std::list<std::string> &paths, std::map<int, std::list<std::string>> &pathsAndLengths)
{
    if (v1 == v2)
    {

        int length = 0;
        std::string current;

        for (auto const &elem : paths)
        {
            if (!current.empty())
            {

                length += weights[std::make_pair(current, elem)];
            }

            if (elem == paths.back())
            {

                pathsAndLengths.insert(std::make_pair(length, paths));
                return;
            }

            current = elem;
        }
    }

    alreadyVisited.insert(v1);

    for (auto const &elem : neighs[v1])
    {

        if (alreadyVisited.count(elem) == 0)
        {

            paths.push_back(elem);
            shortestPathsHelper(elem, v2, alreadyVisited, paths, pathsAndLengths);

            paths.remove(elem);
        }
    }

    alreadyVisited.erase(v1);
}

std::set<std::string> Graph::deadEnds()
{
    std::set<std::string> deadEnds;

    for (auto const &elem : vertices)
    {
        if (neighbours(elem).empty())
        {
            deadEnds.insert(elem);
        }
    }

    return deadEnds;
}

std::list<std::string> Graph::eulerianCycle()
{
    std::map<std::string, std::set<std::string>> neighsCopy = neighs;
    std::list<std::string> path;
    std::string starter;

    if (!isThereEulerianCycle())
    {
        return path;
    }

    for (auto elem : vertices)
    {
        if (neighs[elem].size() - inDegrees(elem) == 1)
        {
            starter = elem;
            break;
        }
        else
        {
            starter = elem;
        }
    }

    eulerianCycleHelper(starter, neighsCopy, path);

    return path;
}

void Graph::eulerianCycleHelper(std::string &v1, std::map<std::string, std::set<std::string>> &neighsCopy,
                                std::list<std::string> &path)
{
    for (auto elem : neighs[v1])
    {
        if (neighsCopy[v1].count(elem) == 1)
        {
            neighsCopy[v1].erase(elem);
            eulerianCycleHelper(elem, neighsCopy, path);
        }
    }

    path.push_front(v1);
}

int Graph::inDegrees(std::string &v)
{
    int counter = 0;
    for (auto const &elem : vertices)
    {
        if (elem == v)
        {
            continue;
        }

        if (hasEdge(elem, v))
        {
            counter++;
        }
    }

    return counter;
}

bool Graph::isThereEulerianCycle()
{

    std::list<std::string> startEndList;

    //at most one vertex has (outdegree) - (indegree) = 1; (condition1)
    //and at most one vertex has (indegree) - (outdegree) = 1; (condition2)
    //and all others have equal in-out degrees (condition3)

    //or all vertices have

    int condition1 = 0;
    int condition2 = 0;
    int condition3 = 0;

    for (auto elem : vertices)
    {

        int inDeg = inDegrees(elem);

        if ((neighs[elem].size() - inDeg) == 1)
        {
            condition1++;
        }
        else if ((inDeg - neighs[elem].size()) == 1)
        {
            condition2++;
        }
        else if (inDeg - neighs[elem].size() == 0)
        {
            condition3++;
        }
    }

    return condition1 == 1 && condition2 == 1 && (condition3 == vertices.size() - 2) ||
           (condition3 == vertices.size());
}

std::set<std::string> &Graph::getVertices()
{
    return this->vertices;
}