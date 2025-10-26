#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "singleton.h"

#include <glm/glm.hpp>

class RenderManager : public singleton<RenderManager>
{
public:
	RenderManager() = default;
	~RenderManager() = default;

public:
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

private:
	glm::mat4 matrix_view = glm::mat4(1.0f);
	glm::mat4 matrix_projection = glm::mat4(1.0f);

public:
	virtual void iInit() override;
	virtual void iUpdate() override;
	virtual void iShutdown() override;
};

#endif