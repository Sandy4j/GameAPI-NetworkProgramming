#ifndef MANUKSYSTEM_H
#define MANUKSYSTEM_H

#include "ManukInterface.h"

struct Transform;

class ManukSystem : public ManukInterface
{
public:
	ManukSystem(Transform* temp_transform, glm::vec3 temp_offset);
	~ManukSystem() = default;

private:
	float RandomNumber(float min, float max);

private:
	Transform* transform;
	glm::vec3 offset;
	float value, radius, speed;

public:
	virtual void IManukStart() override;
	virtual void IManukUpdate() override;
};

#endif
