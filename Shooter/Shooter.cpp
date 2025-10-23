#include "Engine.h"

extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000000;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0;
}

int main()
{
    Engine::INIT();
    Engine::UPDATE();
    Engine::SHUTDOWN();
}