#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "glm/glm.hpp"

#include "Transform.h"
#include "Personal.h"

class EnemySystem
{
public:
	EnemySystem(Transform* temp_transform) : transform(temp_transform) {};
	~EnemySystem() = default;

public:
	void Start();
	void Update();

private:
	glm::vec3 target_position[5];
	Transform* transform;
	float target;
	int index;
	int dir;
};

#endif
