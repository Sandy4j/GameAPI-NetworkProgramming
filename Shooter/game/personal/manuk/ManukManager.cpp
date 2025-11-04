#include <random>
#include <fstream>
#include <string>
#include <iostream>

#include "Entity.h"
#include "Transform.h"
#include "SpriteSystem.h"
#include "ManukSystem.h"

#include "FactoryComponents.h"
#include "GameManager.h"

#include "Level.h"

#include "ManukManager.h"

void ManukManager::FindComponents()
{
    entity = GameManager::GetInstance().GetLevel()->GetEntity();
    sprite_system = GameManager::GetInstance().GetLevel()->GetSpriteSystem();
}

void ManukManager::LoadPrefabs()
{
    std::ifstream file("assets/prefabs/manuk_prefabs.json");

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

void ManukManager::InitPrefabs(json temp, int index)
{
    int id = FactoryComponents::InstantiatePrefab(temp, entity, glm::zero<glm::vec3>(), glm::vec2(0, 0), glm::vec3(1, 1, 0));

    std::string tex = "assets/character/manuk-" + std::to_string(index) + ".png";
    float y = (index % 2 == 0) ? .01 : -.01;
    glm::vec3 offset = glm::zero<glm::vec3>();
    offset.x = -.35 + ((1.25f / 3.0f) * index-1);
    offset.y = .35 + y;

    Sprite* temp_sprite = entity->GetComponent<Sprite>(id);
    temp_sprite->ChangeTexture(tex);
    Transform* temp_transform = entity->GetComponent<Transform>(id);
    ManukInterface* system = new ManukSystem(temp_transform, offset);
    manuk_interfaces.push_back(system);
}

void ManukManager::CreateEntity()
{
    json object = prefabs["Object"];

    for (size_t i = 1; i < 4; i++)
    {
        InitPrefabs(object, i);
    }
}

void ManukManager::IPersonalStart()
{
    FindComponents();
    LoadPrefabs();

    for (auto& temp : manuk_interfaces)
    {
        temp->IManukStart();
    }

    sprite_system->SpriteBegin();
}

void ManukManager::IPersonalUpdate()
{
    for (auto& temp : manuk_interfaces)
    {
        temp->IManukUpdate();
    }
}
