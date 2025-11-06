#include <random>
#include <iostream>
#include <cmath>

#include "Transform.h"

#include "TimeManager.h"

#include "AwanSystem.h"

AwanSystem::AwanSystem(Transform* temp_transform, glm::vec3 temp_offset) :
	transform(temp_transform), offset(temp_offset)
{
    float scale = RandomNumber(.15, .2);
    radius = RandomNumber(.025, .1);
    speed = RandomNumber(-.7, .7);
    transform->scale = glm::vec3(scale, scale, 0);
    transform->position = offset;
}

float AwanSystem::RandomNumber(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(min, max);
    float random_number = distrib(gen);
    return random_number;
}

void AwanSystem::IAwanStart()
{
    transform->position = offset;
}

void AwanSystem::IAwanUpdate()
{
    float deltatime = TimeManager::GetInstance().GetDeltaTime() * speed;
    value += deltatime;
    float sin = std::sin(value);
    float cos = std::cos(value);
    glm::vec3 pos = glm::zero<glm::vec3>();
    pos.y += sin;
    pos.x += cos;
    pos *= radius;
    transform->position = glm::vec3(offset + pos);
}
