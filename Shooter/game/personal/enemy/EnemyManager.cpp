#include <random>
#include <fstream>
#include <iostream>

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

        id = FactoryComponents::InstantiatePrefab(object, entity, glm::zero<glm::vec3>(), glm::vec2(0, 70), glm::vec3(.3, .3, 0));

        entity->GetComponent<Sprite>(id)->ChangeTexture(ikan_paths[RandomNumber(0, 3)]);
        Transform* temp = entity->GetComponent<Transform>(id);
        EnemySystem* system = new EnemySystem(temp);
        enemys.push_back(system);
    }

    SpriteSystem* temp = GameManager::GetInstance().GetLevel()->GetSpriteSystem();
    temp->SpriteBegin();
}

int EnemnyManager::RandomNumber(int min, int max)
{
    int n = max;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(min, n);
    int random_number = distrib(gen);
    return random_number;
}

void EnemnyManager::IPersonalStart()
{
    ikan_paths[0] = "assets/character/ikan-merah.png";
    ikan_paths[1] = "assets/character/ikan-hijau.png";
    ikan_paths[2] = "assets/character/ikan-ungu.png";
    ikan_paths[3] = "assets/character/ikan-kuning.png";

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
