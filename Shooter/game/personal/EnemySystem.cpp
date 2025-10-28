#include <ctime>
#include <random>
#include <glm/glm.hpp>

#include "TimeManager.h"

#include "EnemySystem.h"

void EnemySystem::Start()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(-.5f, .5f);

    float random_float = distrib(gen);

	transform->position = glm::vec3(random_float, random_float, 0);

    target = (random_float > 0)? -.5f : .5f;
    dir = (target > 0) ? -1 : 1;
}

void EnemySystem::Update()
{
    transform->position.x += .1 * dir * TimeManager::GetInstance().GetDeltaTime();

    if (std::abs(transform->position.x) >= std::abs(target))
    {
        target = (target > 0) ? -.5f : .5f;
        dir = (target > 0) ? -1 : 1;
    }
}