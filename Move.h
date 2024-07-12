#ifndef MOVE_H
#define MOVE_H

#include "agv_map.pb.h"
#include "MyEdge.h"
#include <iostream>

class Move
{
public:
    agv_map::Position getStartPosition() const;
    agv_map::Position getEndPosition() const;
    int getStartNodeId() const;
    int getEndNodeId() const;
    int getStartPositionX() const;
    int getStartPositionY() const;
    int getEndPositionX() const;
    int getEndPositionY() const;
    float getStartAngle() const;
    float getEndAngle() const;
    bool getVehicleDirection() const;
    int getLength() const;
    bool isFinalMove();

    static agv_map::Position aimPosition;   //终点的位置，包括x，y坐标，车头的朝向
    

    MyEdge* moveEdge;
    Move* lastMove;
    int lengthG;    // 当前点到起点的距离
    int lengthF;    // 当前点到终点的曼哈顿距离
    int length;
    bool isForward;

    void printMove();

    Move(MyEdge* moveEdge, Move* lastMove);
    Move(const Move& other);
};

class MoveCmp
{
public:
    bool operator()(const Move* move_1, const Move* move_2) const
    { 
        return move_1->length > move_2->length; //升序
    }
};

class MoveHash
{
public:
    size_t operator() (const Move* move) const
    {
        size_t h1 = std::hash<int>()(move->getStartPositionX());
        size_t h2 = std::hash<int>()(move->getStartPositionY());
        size_t h3 = std::hash<int>()(move->getEndPositionX());
        size_t h4 = std::hash<int>()(move->getEndPositionY());
        size_t h5 = std::hash<bool>()(move->getVehicleDirection());
        size_t combinedHash = h1;
        combinedHash = combinedHash ^ (h2 << 1);
        combinedHash = combinedHash ^ (h3 << 2);
        combinedHash = combinedHash ^ (h4 << 3);
        combinedHash = combinedHash ^ (h5 << 4);
        return combinedHash;
    }
};

class MoveEqualTo
{
public:
    bool operator() (const Move* move_1, const Move* move_2) const
    {
        return  move_1->getStartPositionX() == move_2->getStartPositionX() &&
                move_1->getStartPositionY() == move_2->getStartPositionY() &&
                move_1->getEndPositionX() == move_2->getEndPositionX() &&
                move_1->getEndPositionY() == move_2->getEndPositionY() &&
                move_1->getVehicleDirection() == move_2->getVehicleDirection();
    }
};

#endif