#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include "GameManager.h"

#include <glm/gtx/dual_quaternion.hpp>

#include "RenderManager.h"

glm::mat4 RenderManager::GetViewMatrix()
{
	matrix_view = glm::mat4(1.0f);
	return matrix_view = glm::translate(matrix_view, glm::vec3(0, 0, -1.5f));;
}

glm::mat4 RenderManager::GetProjectionMatrix()
{
	matrix_projection = glm::mat4(1.0f);
	return matrix_projection = glm::perspective(glm::radians(45.0f), (float)(600 / 600), .01f, 1000.0f);;
}

void RenderManager::iInit()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderManager::iUpdate()
{
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, GameManager::GetInstance().GetSizeWindow().x, GameManager::GetInstance().GetSizeWindow().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GameManager::GetInstance().GetGameState().UpdateRenderObject();
}

void RenderManager::iShutdown()
{

}
