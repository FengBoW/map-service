#include "Move.h"

agv_map::Position Move::aimPosition;

agv_map::Position Move::getStartPosition() const
{
    return this->moveEdge->edge->basic().start_pos();
}

agv_map::Position Move::getEndPosition() const
{
    return this->moveEdge->edge->basic().end_pos();
}

int Move::getStartNodeId() const
{
    return this->moveEdge->edge->basic().start_id();
}

int Move::getEndNodeId() const
{
    return this->moveEdge->edge->basic().end_id();;
}

int Move::getStartPositionX() const
{
    return this->getStartPosition().x();
}

int Move::getStartPositionY() const
{
    return this->getStartPosition().y();
}

int Move::getEndPositionX() const
{
    return this->getEndPosition().x();
}

int Move::getEndPositionY() const
{
    return this->getEndPosition().y();
}

float Move::getStartAngle() const
{
    return this->getStartPosition().angle();
}

float Move::getEndAngle() const
{
    return this->getEndPosition().angle();
}

bool Move::getVehicleDirection() const
{
    return this->moveEdge->edge->basic().orientation_angle() == 0.f ? true : false;
}

int Move::getLength() const
{
    return this->length;
}

bool Move::isFinalMove()
{
    if(this->getEndPositionX() == Move::aimPosition.x() && this->getEndPositionY() == Move::aimPosition.y())
    {       
        if(this->isForward && Move::aimPosition.angle() == 0.f)
        {
            return true;
        }

        if(this->isForward == false && Move::aimPosition.angle() == 180.f)
        {
            return true;
        }
    }
    return false;
}

void Move::printMove()
{
    std::cout << "[";
    std::cout << this->moveEdge->edge->basic().start_id();
    std::cout << ", ";
    std::cout << this->moveEdge->edge->basic().end_id();
    std::cout << "]" << std::endl;
}

Move::Move(MyEdge *_moveEdge, Move *_lastMove)
{
    
    this->moveEdge = _moveEdge;
    this->lastMove = _lastMove;
    int temp = this->moveEdge->edge->basic().seglen();
    if(this->lastMove)
    {
        this->lengthG = this->lastMove->lengthG + temp;
    } 
    else
    {
        this->lengthG = temp;
    }
    this->lengthF = abs(Move::aimPosition.x() - this->getEndPositionX()) + abs(Move::aimPosition.y() - this->getEndPositionY());
    this->length = this->lengthG + this->lengthF;
    this->isForward = _lastMove == nullptr ? true : _lastMove->isForward;  
}

Move::Move(const Move &other)
{ 
    moveEdge = other.moveEdge;  // 浅拷贝，如果需要深拷贝，需要复制 MyEdge 对象
    lastMove = other.lastMove;  // 浅拷贝，如果需要深拷贝，需要复制 Move 对象
    lengthG = other.lengthG;
    lengthF = other.lengthF;
    length = other.length;
}
