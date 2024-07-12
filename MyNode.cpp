#include "MyNode.h"

void MyNode::addAdjacentNode(int adjacentNodeId)
{
    for (auto id : this->adjacentNode)
    {
        if (id == adjacentNodeId)
        {
            return;
        }       
    }
    adjacentNode.push_back(adjacentNodeId);
};

std::vector<int> MyNode::getAdjacentNode()
{
    return this->adjacentNode;
}

int MyNode::getX()
{
    return this->node.basic().coord().x();
}

int MyNode::getY()
{
    return this->node.basic().coord().y();
}

MyNode::MyNode()
{
    
}

MyNode::MyNode(agv_map::Node agv_map_node)
{
    node = agv_map_node;
}

void MyNode::printNode()
{
    std::cout << this->node.basic().id();
    std::cout << ":(";
    std::cout << this->node.basic().coord().x();
    std::cout << ", ";
    std::cout << this->node.basic().coord().y();
    std::cout << ")" << std::endl;
}
