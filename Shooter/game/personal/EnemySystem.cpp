//#include <ctime>
//#include <random>
#include <glm/glm.hpp>

#include "TimeManager.h"

#include "EnemySystem.h"

void EnemySystem::Start()
{
    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(-.5f, .5f);

    float random_float = distrib(gen);

	transform->position = glm::vec3(random_float, random_float, 0);

    target = (random_float > 0)? -.5f : .5f;
    dir = (target > 0) ? -1 : 1;*/

    target_position[0] = glm::vec3(-.5, 0, 0);
    target_position[1] = glm::vec3(-.25, .35, 0);
    target_position[2] = glm::vec3(0, .5, 0);
    target_position[3] = glm::vec3(.25, .35, 0);
    target_position[4] = glm::vec3(.5, 0, 0);

    index = 0;
    dir = 1;
}

void EnemySystem::Update()
{
    glm::vec3 currentPos = transform->position;
    glm::vec3 targetPos = target_position[index];

    glm::vec3 moveDirection = targetPos - currentPos;
    float distanceToTarget = glm::length(moveDirection);

    const float threshold = 0.01f;
    if (distanceToTarget < threshold)
    {
        transform->position = targetPos;

        int nextIndex = index + dir;

        if (nextIndex >= 5)
        {
            dir = -1;
            index = 0;
        }
        else if (nextIndex < 0)
        {
            dir = 1;
            index = 0;
        }
        else
        {
            index = nextIndex;
        }
    }
    else
    {
        moveDirection = glm::normalize(moveDirection);

        float moveAmount = .75 * TimeManager::GetInstance().GetDeltaTime();

        if (moveAmount > distanceToTarget) 
        {
            moveAmount = distanceToTarget;
        }

        transform->position += moveDirection * moveAmount;
    }
}