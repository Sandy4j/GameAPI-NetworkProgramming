#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BoundingBox.h"

struct Transform
{
public:
	glm::mat4 matrix_model = glm::mat4(1.0f);;
	glm::vec3 position;
	glm::vec2 rotation;
	//float rotation;
	glm::vec3 scale;
	//BoundingBox bounding_box;

public:
	void Update()
	{
		matrix_model = glm::mat4(1.0f);

		matrix_model = glm::translate(matrix_model, position);
		//matrix_model = glm::rotate(matrix_model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix_model = glm::rotate(matrix_model, glm::radians(rotation.x), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix_model = glm::rotate(matrix_model, glm::radians(rotation.y), glm::vec3(0.0f, 0.0f, 1.0f));
		matrix_model = glm::scale(matrix_model, scale);
	}
};

#endif
