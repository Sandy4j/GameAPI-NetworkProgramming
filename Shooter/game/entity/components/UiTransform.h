#ifndef UITRANSFORM_H
#define UITRANSFORM_H

#include <glm/glm.hpp>

struct UiTransform
{
public:
	glm::vec3 position;
	glm::vec3 scale;
	bool b_is_active;
};

#endif