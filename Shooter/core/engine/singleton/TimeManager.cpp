#include <GLFW/glfw3.h>

#include "TimeManager.h"

float& TimeManager::GetDeltaTime()
{
	return delta_time;
}

void TimeManager::CalculateDeltaTime()
{
	float current_deltatime = glfwGetTime();
	delta_time = current_deltatime - last_delta_time;
	last_delta_time = current_deltatime;
}

void TimeManager::iInit()
{
	CalculateDeltaTime();
}

void TimeManager::iUpdate()
{
	CalculateDeltaTime();
}

void TimeManager::iShutdown()
{

}
