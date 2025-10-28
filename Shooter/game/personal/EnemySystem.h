#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

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
	Transform* transform;
};

#endif
