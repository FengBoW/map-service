#ifndef MYNODE_H
#define MYNODE_H

#include "agv_map.pb.h"
#include <unordered_set>
#include <iostream>

using namespace google::protobuf;

class MyNode
{
public: 

    agv_map::Node node;
    std::vector<int> adjacentNode;

    int getX();
    int getY();
    std::vector<int> getAdjacentNode();
    void addAdjacentNode(int adjacentNodeId);

    MyNode();
    MyNode(agv_map::Node agv_map_node);

    void printNode();
};

#endif