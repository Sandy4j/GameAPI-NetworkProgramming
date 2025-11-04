#include <random>
#include <iostream>
#include <cmath>

#include "Transform.h"

#include "TimeManager.h"

#include "AwanSystem.h"

AwanSystem::AwanSystem(Transform* temp_transform) :
	transform(temp_transform)
{
    float scale = RandomNumber(.15, .2);
    transform->scale = glm::vec3(scale, scale, 0);

    //transform->position.x = -1;
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
    transform->position = glm::vec3(0, 0, 0);
}

void AwanSystem::IAwanUpdate()
{
    float deltatime = TimeManager::GetInstance().GetDeltaTime() * .1;
    y_position += deltatime;
    float sin = std::sin(y_position);
    //sin /= 10;
    glm::vec3 pos = transform->position;
    pos.x += deltatime * 10;
    pos.y += sin;
    pos *= .1;
    transform->position = glm::vec3(pos);
}
