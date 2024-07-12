#ifndef MYEDGE_H
#define MYEDGE_H

#include "MyEdge.h"
#include "MyNode.h"
#include "agv_map.pb.h"
#include "Move.h"
#include <unordered_map>
#include <iostream>

using namespace std;

class pairHash 
{
public:
    size_t operator() (const std::pair<int, int>& p) const 
    {
        size_t h1 = std::hash<int>()(p.first);
        size_t h2 = std::hash<int>()(p.second);
        return h1 ^ (h2 << 1);
    }
};

struct pair_equal {
    template <class T1, class T2>
    bool operator() (const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) const {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

class MyMap
{
public:
    std::unordered_map<int, MyNode> myNodes;
    std::unordered_map<std::pair<int, int>, MyEdge, pairHash, pair_equal> myEdges;

    MyMap(agv_map::Map map);

    void printMap();
    bool checkAccessible(Move* move);
};

#endif