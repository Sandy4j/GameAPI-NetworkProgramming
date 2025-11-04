#ifndef AWANSYSTEM_H
#define AWANSYSTEM_H

#include "AwanInterface.h"

struct Transform;

class AwanSystem : public AwanInterface
{
public:
	AwanSystem(Transform* temp_transform);
	~AwanSystem() = default;

private:
	float RandomNumber(float min, float max);

private:
	Transform* transform;
	float y_position;

public:
	virtual void IAwanStart() override;
	virtual void IAwanUpdate() override;
};

#endif
