#include <fstream>
#include <iostream>
#include <string>

#include "Entity.h"
#include "EnemySystem.h"

#include "FactoryComponents.h"
#include "GameManager.h"
#include "SpriteSystem.h"

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

    for (size_t i = 0; i < 2; i++)
    {
        int id = 0;

        id = FactoryComponents::InstantiatePrefab(object, entity, glm::zero<glm::vec3>(), 0, glm::vec3(.1, .1, 0));

        Transform* temp = entity->GetComponent<Transform>(id);
        EnemySystem* system = new EnemySystem(temp);
        enemys.push_back(system);
    }

    SpriteSystem* temp = GameManager::GetInstance().GetLevel()->GetSpriteSystem();
    temp->SpriteBegin();
}

void EnemnyManager::IPersonalStart()
{
	std::cout << "start" << std::endl;
	entity = GameManager::GetInstance().GetLevel()->GetEntity();
	LoadPrefabs();

    for (auto& temp : enemys)
    {
        temp->Start();
    }
}

void EnemnyManager::IPersonalUpdate()
{
    for (auto& temp : enemys)
    {
        temp->Update();
    }
}
