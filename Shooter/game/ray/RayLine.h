#ifndef RAYLINE_H
#define RAYLINE_H

#include <glm/glm.hpp>

class Entity;
class Sprite;
struct GLFWwindow;

class RayLine
{
public:
	RayLine(Entity& temp) : entity(temp) { }
	~RayLine() = default;

private:
	Entity& entity;
	glm::vec3 CalculateRayLine(const glm::mat4& projection, const glm::mat4& view);
	bool CheckRayAABBIntersection(const glm::vec3& ray_origin, const glm::vec3& ray_direction, const glm::vec3& box_min, const glm::vec3& box_max, float& distance);

public:
	int ShootRayLine();

};

#endif