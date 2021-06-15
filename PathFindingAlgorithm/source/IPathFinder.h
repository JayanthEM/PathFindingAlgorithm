#pragma once
#include "Position.h"
#include <string>

class IPathFinder
{
    virtual void FindPath(Position start, Position end) = 0;
    virtual std::string GetName() = 0;
};