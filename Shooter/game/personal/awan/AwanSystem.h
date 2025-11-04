#ifndef AWANSYSTEM_H
#define AWANSYSTEM_H

#include "AwanInterface.h"

struct Transform;

class AwanSystem : public AwanInterface
{
public:
	AwanSystem(Transform* temp_transform, glm::vec3 temp_offset);
	~AwanSystem() = default;

private:
	float RandomNumber(float min, float max);

private:
	Transform* transform;
	glm::vec3 offset;
	float value, radius, speed;

public:
	virtual void IAwanStart() override;
	virtual void IAwanUpdate() override;
};

#endif
