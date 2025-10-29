#include <glm/glm.hpp>
#include <algorithm>
#include <random>
#include <chrono>

#include "TimeManager.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(Transform* temp_transform)
    : transform(temp_transform),
    m_currentState(MovementState::Idle),
    m_hasTarget(false),
    m_jumpElapsedTime(0.0f),
    m_moveSpeed(0.5f),
    m_decisionTimer(0.0f),
    m_idleTimer(0.0f),
    m_minBounds(-1.0f, -1.0f),
    m_maxBounds(1.0f, 1.0f),
    m_fixedZ(-1.5f),          
    m_rng(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
    m_distFloat(0.0f, 1.0f),
    m_distDecision(1, 100)
{
}

void EnemySystem::Start()
{
    float startX = m_minBounds.x + (m_maxBounds.x - m_minBounds.x) * m_distFloat(m_rng);
    transform->position = glm::vec3(startX, -1.4, m_fixedZ);

    m_decisionTimer = 1.0f + 2.0f * m_distFloat(m_rng);
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
    m_currentState = MovementState::Jumping;
    m_jumpStartPos = transform->position;

    float endX = m_minBounds.x + (m_maxBounds.x - m_minBounds.x) * m_distFloat(m_rng);
    m_jumpEndPos = glm::vec3(endX, m_jumpStartPos.y, m_fixedZ);

    m_jumpControlPos = (m_jumpStartPos + m_jumpEndPos) / 2.0f;
    float randomHeight = 1.5f + 2.0f * m_distFloat(m_rng);
    m_jumpControlPos.y = m_jumpStartPos.y + randomHeight; 
    m_jumpControlPos.z = m_fixedZ;

    m_jumpDuration = 1.0f + 1.0f * m_distFloat(m_rng);
    m_jumpElapsedTime = 0.0f;
}

void EnemySystem::PickNewTarget()
{
    float targetX = m_minBounds.x + (m_maxBounds.x - m_minBounds.x) * m_distFloat(m_rng);
    float targetY = transform->position.y;
    m_targetPos = glm::vec3(targetX, targetY, m_fixedZ);
    m_hasTarget = true;
    m_currentState = MovementState::Moving;
}

void EnemySystem::Update()
{
    float deltaTime = TimeManager::GetInstance().GetDeltaTime();

    if (m_decisionTimer > 0.0f) 
    {
        m_decisionTimer -= deltaTime;
    }

    switch (m_currentState)
    {
    case MovementState::Idle:
        m_idleTimer -= deltaTime;
        if (m_idleTimer <= 0.0f) 
        {
            int decisionRoll = m_distDecision(m_rng);
            if (decisionRoll <= 70) 
                PickNewTarget();
            else
                InitiateJump();
        }
        break;
    case MovementState::Moving:
        if (!m_hasTarget)
            PickNewTarget();

        glm::vec3 currentPos = transform->position;
        glm::vec3 targetPos = m_targetPos;
        glm::vec3 moveDirection = targetPos - currentPos;
        float distanceToTarget = glm::length(glm::vec2(moveDirection.x, moveDirection.y));

        const float threshold = 0.05f;
        if (distanceToTarget < threshold) 
        {
            transform->position = targetPos;
            m_hasTarget = false;
            m_idleTimer = 0.5f + 1.0f * m_distFloat(m_rng);
            m_currentState = MovementState::Idle;
        }
        else 
        {
            moveDirection = glm::normalize(moveDirection);
            float moveAmount = m_moveSpeed * deltaTime;
            if (moveAmount > distanceToTarget) moveAmount = distanceToTarget;
            transform->position += moveDirection * moveAmount;

            if (m_decisionTimer <= 0.0f) 
            {
                int decisionRoll = m_distDecision(m_rng);
                if (decisionRoll > 90) 
                {
                    InitiateJump();
                    m_decisionTimer = 2.0f + 3.0f * m_distFloat(m_rng);
                }
                else
                    m_decisionTimer = 0.5f + 1.5f * m_distFloat(m_rng);
            }
        }
        break;
    case MovementState::Jumping:
        m_jumpElapsedTime += deltaTime;
        float t = std::min(1.0f, m_jumpElapsedTime / m_jumpDuration);

        transform->position = CalculateBezierPoint(t, m_jumpStartPos, m_jumpControlPos, m_jumpEndPos);
        transform->position.z = m_fixedZ;

        if (t >= 1.0f) 
        {
            transform->position.y = m_jumpEndPos.y;
            m_idleTimer = 0.5f + 1.0f * m_distFloat(m_rng);
            m_currentState = MovementState::Idle;
        }
        break;
    }
}