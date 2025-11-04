#include <random>
#include <fstream>
#include <iostream>

#include "Entity.h"
#include "Transform.h"
#include "SpriteSystem.h"
#include "AwanSystem.h"

#include "FactoryComponents.h"
#include "GameManager.h"

#include "Level.h"

#include "AwanManager.h"

void AwanManager::FindComponents()
{
    entity = GameManager::GetInstance().GetLevel()->GetEntity();
    sprite_system = GameManager::GetInstance().GetLevel()->GetSpriteSystem();
}

void AwanManager::LoadPrefabs()
{
    std::ifstream file("assets/prefabs/awan_prefabs.json");

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

void AwanManager::InitPrefabs(json temp)
{
    int id = FactoryComponents::InstantiatePrefab(temp, entity, glm::zero<glm::vec3>(), glm::vec2(0, 0), glm::vec3(1, 1, 0));

    std::string tex = (id % 2 == 0)? "assets/environment/awan-1.png" : "assets/environment/awan-2.png";

    Sprite* temp_sprite = entity->GetComponent<Sprite>(id);
    temp_sprite->ChangeTexture(tex);
    Transform* temp_transform = entity->GetComponent<Transform>(id);
    AwanInterface* system = new AwanSystem(temp_transform);
    awan_interfaces.push_back(system);
}

void AwanManager::CreateEntity()
{
    json object = prefabs["Object"];

    for (size_t i = 0; i < 5; i++)
    {
        InitPrefabs(object);
    }
}

void AwanManager::IPersonalStart()
{
    std::cout << "START AWAN" << std::endl;

    FindComponents();
    LoadPrefabs();

    for (auto& temp : awan_interfaces)
    {
        temp->IAwanStart();
    }

    sprite_system->SpriteBegin();
}

void AwanManager::IPersonalUpdate()
{
    for (auto& temp : awan_interfaces)
    {
        temp->IAwanUpdate();
    }
}
