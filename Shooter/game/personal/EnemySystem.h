#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "Personal.h"

class EnemySystem : public Personal
{
public:
	EnemySystem() = default;
	~EnemySystem() = default;

public:
	virtual void IPersonalStart() override;
	virtual void IPersonalUpdate() override;
};

#endif
