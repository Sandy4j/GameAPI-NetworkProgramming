#include <ctime>
#include <random>
#include <glm/glm.hpp>

#include "EnemySystem.h"

void EnemySystem::Start()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(-.5f, .5f);

    float random_float = distrib(gen);

	transform->position = glm::vec3(random_float, random_float, 0);
}

void EnemySystem::Update()
{

}