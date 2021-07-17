#pragma once
#include <stdint.h>

class Position
{
public:
    Position() {}
    Position(int32_t _y, int32_t _x) : x(_x), y(_y){};

    int32_t X() { return x; }
    int32_t Y() { return y; }

    bool operator<(const Position &position) const
    {
        return (x < position.x) || (x == position.x && y < position.y);
    }


    void operator=(const Position& position)
    {
        x = position.x;
        y = position.y;
    }

    bool operator == (const Position & position)
    {
        return x == position.x  && y == position.y;
    }

    bool operator != (const Position& position)
    {
        return ( (x != position.x) || (y != position.y) );
    }
    
private:
    int32_t x;
    int32_t y;

};