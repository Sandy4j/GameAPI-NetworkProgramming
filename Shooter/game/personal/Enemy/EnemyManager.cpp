#include <fstream>
#include <iostream>
#include <string>

#include "Entity.h"
#include "EnemySystem.h"

#include "FactoryComponents.h"
#include "GameManager.h"

#include "Level.h"

#include "EnemyManager.h"

void EnemnyManager::LoadPrefabs()
{
    std::ifstream file("assets/prefabs/enemy_prefabs.json");

    if (!file.is_open())
    {
        std::cerr << "Failed to open level file!\n";
        return;
    }

    try
    {
        file >> prefabs;

        CreateEntity();

        std::cout << "LOAD JSON PREFABS" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "JSON error: " << e.what() << std::endl;
    }
}

void EnemnyManager::CreateEntity()
{
    json object = prefabs["Object"];

    for (auto& [name, obj] : object.items())
    {
        std::cout << "Create Entity Prefabs" << std::endl;
        FactoryComponents::CreateObjectComponents(obj, entity);
    }
}

void EnemnyManager::IPersonalStart()
{
	std::cout << "start" << std::endl;
	entity = GameManager::GetInstance().GetLevel()->GetEntity();
	LoadPrefabs();
}

void EnemnyManager::IPersonalUpdate()
{

}
