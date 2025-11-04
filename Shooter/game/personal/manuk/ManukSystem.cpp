#include <random>
#include <iostream>
#include <cmath>

#include "Transform.h"

#include "TimeManager.h"

#include "ManukSystem.h"

ManukSystem::ManukSystem(Transform* temp_transform, glm::vec3 temp_offset) :
	transform(temp_transform), offset(temp_offset)
{
    float scale = RandomNumber(.15, .25);
    radius = RandomNumber(.025, .075);
    speed = (RandomNumber(-.7, .7) >= 0.0)? .5 : -.5;
    transform->scale = glm::vec3(scale, scale, 0);
    transform->position = offset;
}

float ManukSystem::RandomNumber(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(min, max);
    float random_number = distrib(gen);
    return random_number;
}

void ManukSystem::IManukStart()
{ 
    transform->position = offset;
}

void ManukSystem::IManukUpdate()
{
    float deltatime = TimeManager::GetInstance().GetDeltaTime() * speed;
    value += deltatime;
    float sin = std::sin(value);
    float wave_motion_y = sin * radius;
    transform->position.x += deltatime * .1;
    transform->position.y = offset.y + wave_motion_y;
    transform->position.z = offset.z;

    int dir = (speed > 0)? 1 : -1;
    if (std::abs(transform->position.x) >= 1) transform->position.x = -1 * dir;
}
