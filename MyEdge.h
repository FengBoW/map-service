#ifndef MY_EDGE_H
#define MY_EDGE_H

#include "agv_map.pb.h"
#include <iostream>

class MyEdge
{  
public:
    MyEdge();
    MyEdge(agv_map::Edge* edge);
    MyEdge(const MyEdge& other);
    
    void printEdge();
    agv_map::Edge* edge;
};

#endif