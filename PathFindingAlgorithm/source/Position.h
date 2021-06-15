#pragma once
#include <stdint.h>

class Position
{
public:
    Position(int32_t _x, int32_t _y) : x(_x), y(_y){};

    int32_t X() { return x; }
    int32_t Y() { return y; }

    bool operator<(const Position &pos) const 
    {
        return ((y*2+x) < (pos.y*2+pos.x));
    }

private:
    int32_t x;
    int32_t y;

};