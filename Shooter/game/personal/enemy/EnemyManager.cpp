#include <random>
#include <fstream>
#include <iostream>

#include "Entity.h"
#include "UiTransform.h"
#include "Timer.h"
#include "EnemySystem.h"

#include "FactoryComponents.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "SpriteSystem.h"

#include "Level.h"

#include "EnemyManager.h"

void EnemyManager::Init()
{
    FindComponent();
    LoadPrefabs();

    current_state = EState::TransitionState;
}

void EnemyManager::LoadPrefabs()
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

void EnemyManager::FindComponent()
{
    ikan_paths[0] = "assets/character/ikan-hijau.png";
    ikan_paths[1] = "assets/character/ikan-kuning.png";
    ikan_paths[2] = "assets/character/ikan-ungu.png";
    ikan_paths[3] = "assets/character/ikan-merah.png";

    entity = GameManager::GetInstance().GetLevel()->GetEntity();
    sprite_system = GameManager::GetInstance().GetLevel()->GetSpriteSystem();

    Personal* raw_timer = entity->GetComponent<Personal>(1002);
    timer = static_cast<Timer*>(raw_timer);

    transition_delay = 2;
    start_enemy = 2;
    total_enemy = start_enemy;
}

void EnemyManager::CreateEntity()
{
    json object = prefabs["Object"];

    for (size_t i = 0; i < total_enemy; i++)
    {
        InitPrefabs(object);
    }
}

void EnemyManager::InitPrefabs(json temp)
{
    int id = 0;

    float scale = RandomNumberFloat(.15, .3);
    id = FactoryComponents::InstantiatePrefab(temp, entity, glm::zero<glm::vec3>(), glm::vec2(0, 0), glm::vec3(scale, scale, 0));

    int random_number = RandomNumber(0, 3);
    int score = random_number + 10;
    entity->GetComponent<Sprite>(id)->ChangeTexture(ikan_paths[random_number]);
    Transform* temp_transform = entity->GetComponent<Transform>(id);
    temp_transform->tag = std::to_string(score);
    Sprite* temp_sprite = entity->GetComponent<Sprite>(id);
    EnemyInterface* system = new EnemySystem(temp_transform, temp_sprite);
    //enemy_pools.push_back(system);
    enemys.push_back(system);
}

int EnemyManager::RandomNumber(int min, int max)
{
    int n = max;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(min, n);
    int random_number = distrib(gen);
    return random_number;
}

float EnemyManager::RandomNumberFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(min, max);
    float random_number = distrib(gen);
    return random_number;
}

void EnemyManager::StartWaveEnemy()
{
    int temp = GameManager::GetInstance().GetWave();
    temp++;
    GameManager::GetInstance().SetWave(temp);
    std::cout << GameManager::GetInstance().GetWave() << std::endl;
    //wave_index++;
    //total_enemy = start_enemy + wave_index;
    //start_enemy = total_enemy;

    ///*if (total_enemy > enemy_pools.size())
    //{
    //    json object = prefabs["Object"];
    //    int size = total_enemy - enemy_pools.size();

    //    for (int i = 0; i < size; i++)
    //    {
    //        InitPrefabs(object);
    //    }
    //}*/

    //int enemiesToMove = std::min((int)enemy_pools.size(), total_enemy);

    //for (int i = 0; i < enemiesToMove; i++)
    //{
    //    enemys.push_back(enemy_pools[0]);
    //    enemy_pools.erase(enemy_pools.begin());
    //}

    for (auto& temp : enemys)
    {
        temp->IStartEnemy();
    }

    sprite_system->SpriteBegin();
    timer->StartTimer(100);
}

void EnemyManager::ResetWaveEnemy()
{
    for (auto& temp : enemys)
    {
        temp->IResetEnemy();
    }

    /*for (int i = 0; i < enemys.size(); i++)
    {
        enemy_pools.push_back(enemys[i]);
        enemys.erase(enemys.begin());
    }*/

    /*enemy_pools.insert(enemy_pools.end(), enemys.begin(), enemys.end());
    enemys.clear();
    sprite_system->SpriteBegin();*/
}

void EnemyManager::CheckWaveCondition()
{
    if (!b_is_reset || !enemys.empty())
    {
        int total_hit = 0;
        for (auto& temp : enemys)
        {
            temp->IUpdateEnemy();

            if (temp->IGetLayerEnemy() == -1) total_hit++;
        }

        b_is_reset = total_hit == total_enemy;
    }

    if (b_is_reset)
    {
        std::cout << "reset" << std::endl;

        ResetWaveEnemy();

        timer->StopTimer();
        transition_delay = 2;
        current_state = EState::TransitionState;

        entity->GetComponent<UiTransform>(5)->b_is_active = true;

        std::cout << "TRANSITION" << std::endl;

        b_is_reset = false;
    }

    /*if (!b_is_reset) return;

    std::cout << "reset" << std::endl;

    ResetWaveEnemy();

    timer->StopTimer();
    transition_delay = 2;
    current_state = EState::TransitionState;

    std::cout << "TRANSITION" << std::endl;

    b_is_reset = false;*/
}

bool EnemyManager::StateCondition()
{
    if (current_state == EState::GameplayState) return true;

    if (transition_delay > 0)
    {   
        current_state = EState::TransitionState;
        transition_delay -= TimeManager::GetInstance().GetDeltaTime();
        return false;
    }

    entity->GetComponent<UiTransform>(5)->b_is_active = false;
    ResetWaveEnemy();
    StartWaveEnemy();
    current_state = EState::GameplayState;
    return true;
}

void EnemyManager::IPersonalStart()
{
    Init();
}

void EnemyManager::IPersonalUpdate()
{
    if (!StateCondition()) return;

    CheckWaveCondition();

    /*if (b_is_reset || enemys.empty()) return;

    int total_hit = 0;

    for (auto& temp : enemys)
    {
        temp->IUpdateEnemy();

        if (temp->IGetLayerEnemy() == -1) total_hit++;
    }

    b_is_reset = total_hit == total_enemy;*/
}
