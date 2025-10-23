#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>

struct BoundingBox
{
public:
	bool b_is_trigger = false;
	glm::vec3 min = glm::vec3(-0.5f, -0.5f, 0.0f);
	glm::vec3 max = glm::vec3( 0.5f,  0.5f, 0.0f);
};

#endif