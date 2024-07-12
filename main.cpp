#include <iostream>
#include <fstream>
#include <google/protobuf/util/json_util.h>
#include <vector>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <cstdint>
#include "agv_map.pb.h"
#include "MyMap.h"
#include "Move.h"

using namespace google::protobuf;

void AStar(int startNodeId, int endNodeId, MyMap myMap)
{
    
    std::priority_queue<Move*, std::vector<Move*>, MoveCmp> openList;
    std::unordered_set<Move*, MoveHash, MoveEqualTo> openSet;
    std::unordered_set<Move*, MoveHash, MoveEqualTo> closeSet;

    int workNodeId = startNodeId;
    MyNode workNode = myMap.myNodes[startNodeId];
    std::vector<int> adjacentNode = workNode.getAdjacentNode();
    for(auto nextNodeId : adjacentNode)
    {
        MyEdge* moveEdge = &myMap.myEdges[{workNodeId, nextNodeId}];
        Move* move = new Move(moveEdge, nullptr);

        if( !myMap.checkAccessible(move))
        {
            continue;
        }        

        openList.push(move);
        openSet.insert(move);
        
        // 打印日志
        std::cout << "open入队：";
        move->printMove();        
    }

    while(!openList.empty()) 
    {
        Move* lastMove = openList.top();
        
        if(lastMove->isFinalMove())
        {
            std::cout << "success" << std::endl;
            std::cout << lastMove->isForward << std::endl;
            while(lastMove != nullptr) 
            {
                lastMove->printMove();
                lastMove = lastMove->lastMove;
            }
            return;
        }

        openList.pop();
        openSet.erase(lastMove);

        // 打印日志
        std::cout << "open出队：";
        lastMove->printMove();
      
        closeSet.insert(lastMove);

        // 打印日志
        std::cout << "                              close入队：";
        lastMove->printMove();
        
        workNodeId = lastMove->getEndNodeId();
        workNode = myMap.myNodes[workNodeId];
        std::vector<int> adjacentNode = workNode.getAdjacentNode();
        for(auto nextNodeId : adjacentNode)
        {
            MyEdge* moveEdge = &myMap.myEdges[{workNodeId, nextNodeId}];
            Move* move = new Move(moveEdge, lastMove);

            int x = myMap.checkAccessible(move);
            if(x == 0) 
            {
                std::cout << "wrong" << std::endl;
                continue;
            }
            if (x == -1)
            {
                move->isForward = !move->isForward;
            }
            
            if(closeSet.find(move) == closeSet.end() && openSet.find(move) == closeSet.end())
            {
                openList.push(move);
                openSet.insert(move);

                // 打印日志
                std::cout << "open入队：";
                move->printMove();            
            }           
        }
    }
    return;
};

int main(int argc, char *argv[])
{
    std::ifstream fiRCS("./RCS.pb", std::ios::in | std::ios::binary);
    fiRCS.seekg(2, std::ios::beg);
    
    int size = 0;
    fiRCS.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::cout << "The size is: " << size << std::endl;

    agv_map::MAP_ARR map_arr;
    agv_map::Map map;

    map_arr.ParseFromIstream(&fiRCS);
    map = map_arr.map(1);

    MyMap myMap(map);

    //myMap.printMap();

    int startNodeId = 238;
    int endNodeId = 20;
 
    int x = myMap.myNodes[endNodeId].getX();
    int y = myMap.myNodes[endNodeId].getY();
    Move::aimPosition.set_x(x);
    Move::aimPosition.set_y(y);
    Move::aimPosition.set_angle(180.f);
   
    AStar(startNodeId, endNodeId, myMap);

    return 0;
}
