// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include <glm/glm.hpp>
#include <random>

#include "Transform.h"

class EnemySystem
{
public:
    EnemySystem(Transform* temp_transform);
    ~EnemySystem() = default;

public:
    void Start();
    void Update();

private:
    glm::vec3 CalculateBezierPoint(float t, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2);
    void PickNewTarget();
    void InitiateJump();

    enum class MovementState {
        Idle,
        Moving,
        Jumping
    };
    MovementState m_currentState;

    glm::vec3 m_targetPos;
    bool m_hasTarget;

    glm::vec3 m_jumpStartPos;
    glm::vec3 m_jumpControlPos;
    glm::vec3 m_jumpEndPos;
    float m_jumpDuration;
    float m_jumpElapsedTime;
    glm::vec3 temp_target_pos;

    float m_decisionTimer;
    float m_idleTimer;

    float m_moveSpeed;

    glm::vec2 m_minBounds;
    glm::vec2 m_maxBounds;
    float m_fixedZ;       

    std::mt19937 m_rng;
    std::uniform_real_distribution<float> m_distFloat;
    std::uniform_int_distribution<int> m_distDecision;

    Transform* transform;
};

#endif