#include <glm/glm.hpp>
#include <algorithm>
#include <random>
#include <chrono>

#include "Transform.h"
#include "Sprite.h"

#include "GameManager.h"
#include "TimeManager.h"

#include "EnemySystem.h"

EnemySystem::EnemySystem(Transform* temp_transform, Sprite* temp_sprite)
    : transform(temp_transform),
    sprite(temp_sprite),
    current_state(MovementState::Idle),
    b_is_target(false),
    jump_elapsed_time(0.0f),
    move_speed(0.5f),
    decision_timer(0.0f),
    idle_timer(0.0f),
    min_bounds(-1.0f, -1.0f),
    max_bounds(1.0f, 1.0f),
    fixed_z(-1.5f),          
    rage(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
    dist_float(0.0f, 1.0f),
    dist_decision(1, 100)
{}

void EnemySystem::IResetEnemy()
{
    transform->position = glm::vec3(0, -10, 0);
    b_is_target = false;
    idle_timer = 0.5f + 1.0f * dist_float(rage);
    current_state = MovementState::Idle;
}

void EnemySystem::IStartEnemy()
{
    sprite->layer = 1;

    float startX = min_bounds.x + (max_bounds.x - min_bounds.x) * dist_float(rage);
    transform->position = glm::vec3(startX, -1.4, fixed_z);

    decision_timer = 1.0f + 2.0f * dist_float(rage);
}

glm::vec3 EnemySystem::CalculateBezierPoint(float t, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2)
{
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    glm::vec3 p = uu * p0 + 2.0f * u * t * p1 + tt * p2;
    return p;
}

void EnemySystem::InitiateJump()
{
    current_state = MovementState::Jumping;
    jump_start_position = transform->position;

    float endX = min_bounds.x + (max_bounds.x - min_bounds.x) * dist_float(rage);
    jump_end_position = glm::vec3(endX, jump_start_position.y, fixed_z);

    jump_control_position = (jump_start_position + jump_end_position) / 2.0f;
    float randomHeight = 1.5f + 2.0f * dist_float(rage);
    jump_control_position.y = jump_start_position.y + randomHeight; 
    jump_control_position.z = fixed_z;

    jump_duration = 1.0f + 1.0f / GameManager::GetInstance().GetWave();
    jump_elapsed_time = 0.0f;

    transform->rotation.x = (jump_start_position.x < jump_end_position.x)? 180 : 0;
}

int EnemySystem::IGetLayerEnemy()
{
    return sprite->layer;
}

void EnemySystem::PickNewTarget()
{
    float targetX = min_bounds.x + (max_bounds.x - min_bounds.x) * dist_float(rage);
    float targetY = transform->position.y;
    target_position = glm::vec3(targetX, targetY, fixed_z);
    b_is_target = true;
    current_state = MovementState::Moving;
}

void EnemySystem::IUpdateEnemy()
{
    float deltaTime = TimeManager::GetInstance().GetDeltaTime();

    if (decision_timer > 0.0f) decision_timer -= deltaTime;

    switch (current_state)
    {
    case MovementState::Idle:
    {
        idle_timer -= deltaTime;
        if (idle_timer <= 0.0f) 
        {
            int decisionRoll = dist_decision(rage);
            if (decisionRoll <= 70) 
                PickNewTarget();
            else
                InitiateJump();
        }
        break;
    }
    case MovementState::Moving:
    {
        if (!b_is_target)
            PickNewTarget();

        glm::vec3 currentPos = transform->position;
        glm::vec3 targetPos = target_position;
        glm::vec3 moveDirection = targetPos - currentPos;
        float distanceToTarget = glm::length(glm::vec2(moveDirection.x, moveDirection.y));

        const float threshold = 0.05f;
        if (distanceToTarget < threshold) 
        {
            transform->position = targetPos;
            b_is_target = false;
            idle_timer = 0.5f + 1.0f * dist_float(rage);
            current_state = MovementState::Idle;
        }
        else 
        {
            moveDirection = glm::normalize(moveDirection);
            float moveAmount = move_speed * deltaTime;
            if (moveAmount > distanceToTarget) moveAmount = distanceToTarget;
            transform->position += moveDirection * moveAmount;

            if (decision_timer <= 0.0f) 
            {
                int decisionRoll = dist_decision(rage);
                if (decisionRoll > 90) 
                {
                    InitiateJump();
                    decision_timer = 2.0f + 3.0f * dist_float(rage);
                }
                else
                    decision_timer = 0.5f + 1.5f * dist_float(rage);
            }
        }
        break;
    }
    case MovementState::Jumping:
    {
        jump_elapsed_time += deltaTime;
        float t = std::min(1.0f, jump_elapsed_time / jump_duration);

        transform->position = CalculateBezierPoint(t, jump_start_position, jump_control_position, jump_end_position);
        transform->position.z = fixed_z;

        if (t >= 1.0f) 
        {
            transform->position.y = jump_end_position.y;
            idle_timer = 0.5f + 1.0f * dist_float(rage);
            current_state = MovementState::Idle;
        }
        break;
    }
    }
}