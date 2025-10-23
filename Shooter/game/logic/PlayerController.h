#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <set>
#include <functional>

#include "Entity.h"

enum class EGameState : int;
class RayLine;
struct GLFWwindow;

class PlayerController
{
public:
	PlayerController(Entity& temp_entity);
	~PlayerController() = default;

private:
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	void Shoot();
	void Pause();

private:
	Entity& entity;
	RayLine* ray_line;
};

#endif
