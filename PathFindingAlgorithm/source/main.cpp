#include <SDL.h>
#undef main
#include "GameEngine.h"

int main()
{
    GameEngine engine;
    engine.ConstructEngine();
    engine.GameLoop();
}