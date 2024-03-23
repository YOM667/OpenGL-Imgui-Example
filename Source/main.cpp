#include "GameEngine.h"
int main(int argc, char* argv[])
{
    GameEngine* engine = new GameEngine(Mode::DEV);
    engine->render();
    engine->shutdown();
    return 0;
}