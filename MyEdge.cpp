#include "MyEdge.h"

MyEdge::MyEdge()
{
    std::cout << "MyEdge 默认拷贝构造函数" << std::endl;
}

MyEdge::MyEdge(agv_map::Edge* agv_map_edge)
{
    edge = agv_map_edge;
}

MyEdge::MyEdge(const MyEdge &other)
{    
    
    if (other.edge) {
        this->edge = new agv_map::Edge(*other.edge);  // 深拷贝 agv_map::Edge 对象
    } else {
        this->edge = nullptr;
    }
}

void MyEdge::printEdge()
{
    std::cout << "[";
    std::cout << this->edge->basic().start_id();
    std::cout << ", ";
    std::cout << this->edge->basic().end_id();
    std::cout << "]" << std::endl;
}
