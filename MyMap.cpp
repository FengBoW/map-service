#include "MyMap.h"

MyMap::MyMap(agv_map::Map map)
{
    
    google::protobuf::Map<int32_t, agv_map::Node> agv_map_Map_Node = map.node();
    for (auto it = agv_map_Map_Node.begin(); it != agv_map_Map_Node.end(); it++)
    {
        agv_map::Node node = it->second;
        MyNode myNode(node);
        int id = node.basic().id();
        myNodes.insert(std::pair<int, MyNode>(id, myNode));
    }
    
    google::protobuf::Map<int32_t, agv_map::Segment> agv_map_Map_Segment = map.segment();
    for (auto it = agv_map_Map_Segment.begin(); it != agv_map_Map_Segment.end(); it++)
    {
        agv_map::Segment segment = it->second;

        //解析edge_1
        agv_map::Edge edge_1 = segment.edge_1();
        if(edge_1.basic().enable() != 0) {
            MyEdge myEdge_1(&edge_1);
            int myEdge_1_start_id = edge_1.basic().start_id();
            int myEdge_1_end_id = edge_1.basic().end_id();

            std::pair<int, int> ids{myEdge_1_start_id, myEdge_1_end_id};
            this->myEdges.emplace(ids, myEdge_1);

            auto myNode = myNodes.find(myEdge_1_start_id);
            myNode->second.addAdjacentNode(myEdge_1_end_id);
        }
        
        //解析edge_2
        agv_map::Edge edge_2 = segment.edge_2();
        if(edge_2.basic().enable() != 0) {
            MyEdge myEdge_2(&edge_2);
            int myEdge_2_start_id = edge_2.basic().start_id();
            int myEdge_2_end_id = edge_2.basic().end_id();

            std::pair<int, int> ids{myEdge_2_start_id, myEdge_2_end_id};
            this->myEdges.emplace(ids, myEdge_2);

            auto myNode = myNodes.find(myEdge_2_start_id);
            myNode->second.addAdjacentNode(myEdge_2_end_id);
        }
    }
    
}

void MyMap::printMap()
{
    for (auto n : this->myNodes)
    {
        n.second.printNode();
    }

    for (auto e : this->myEdges)
    {
        e.second.printEdge();
    }
}

bool MyMap::checkAccessible(Move* move)
{
    Move* lastMove = move->lastMove;
    if(lastMove == nullptr)
    {
        return true;
    }
    
    float lastMoveAngle = lastMove->moveEdge->edge->basic().end_pos().angle();
    float nextMoveAngle = move->moveEdge->edge->basic().start_pos().angle();
    
    if(abs(nextMoveAngle - lastMoveAngle) < 45.f) 
    {
        // 正向
        return true;
    }

    float reverAngle = lastMoveAngle + 180;   
    if (reverAngle > 180) {
        reverAngle -= 360;
    } else if (reverAngle < -180) {
        reverAngle += 360;
    }
    if(abs(nextMoveAngle - reverAngle) < 45.f) 
    {
        // 反向
        move->isForward = !move->isForward;
        return true;
    }

    // 走不到
    return false;
}
