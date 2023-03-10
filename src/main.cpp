#include <iostream>
#include <game.h>
#include <debug_system.h>

extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

using namespace rhythm_typer::core;
using namespace rhythm_typer::debug;

int main(int argc, char* argv[])
{
    RTGame& game = RTGame::GetInstance();
    DebugSystem& debug_system = game.AddSystem<DebugSystem>();
    if (!game.Initialize()) {
        std::cout << "Could not initialize game.";
        return -1;
    }
    game.Start();
    return 0;
}