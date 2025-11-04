#include "Engine.h"
#include "Integration/GameAPIManager.h"
#include <iostream>

extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000000;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0;
}

int main()
{
	GameAPIManager::GetInstance().Initialize("https://localhost:7016/api");

    if (GameAPIManager::GetInstance().TestConnection()) {
		std::cout << "Connected to Game API successfully!" << std::endl;
    }

    Engine::INIT();
    Engine::UPDATE();
    Engine::SHUTDOWN();
}