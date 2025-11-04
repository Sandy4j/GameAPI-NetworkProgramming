// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include <glm/glm.hpp>
#include <random>

//#include "Transform.h"
#include "EnemyInterface.h"

struct Transform;
struct Sprite;

enum class MovementState {
    Idle,
    Moving,
    Jumping
};

class EnemySystem : public EnemyInterface
{
public:
    EnemySystem(Transform* temp_transform, Sprite* temp_sprite);
    ~EnemySystem() = default;

private:
    glm::vec3 CalculateBezierPoint(float t, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2);
    void PickNewTarget();
    void InitiateJump();

    MovementState current_state;

    glm::vec3 target_position;
    bool b_is_target;

    glm::vec3 jump_start_position;
    glm::vec3 jump_control_position;
    glm::vec3 jump_end_position;
    float jump_duration;
    float jump_elapsed_time;

    float decision_timer;
    float idle_timer;

    float move_speed;

    glm::vec2 min_bounds;
    glm::vec2 max_bounds;
    float fixed_z;       

    std::mt19937 rage;
    std::uniform_real_distribution<float> dist_float;
    std::uniform_int_distribution<int> dist_decision;

    Transform* transform;
    Sprite* sprite;

public:
    virtual void IResetEnemy() override;
    virtual void IStartEnemy() override;
    virtual void IUpdateEnemy() override;
    virtual int IGetLayerEnemy() override;
};

#endif