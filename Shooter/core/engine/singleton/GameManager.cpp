#include "GameManager.h"

void GameManager::CreateMainWindow(float x, float y)
{
	if (window) return;
	size_window = new glm::vec2(x, y);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
	window = glfwCreateWindow(size_window->x, size_window->y, "GameAPI", NULL, NULL);
	int xPos = (mode->width - size_window->x) / 2;
	int yPos = (mode->height - size_window->y) / 2;
	glfwSetWindowPos(window, xPos, yPos);

	mouse_position = new glm::vec2(0.0f, 0.0f);
}

GLFWwindow* GameManager::GetWindow()
{
	return window;
}

glm::vec2& GameManager::GetSizeWindow()
{
	return *size_window;
}

glm::vec2& GameManager::GetMousePosition()
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	return *mouse_position = glm::vec2(mouseX, mouseY);
}

void GameManager::SetIsExit(bool value)
{
	b_is_exit = value;
}

bool GameManager::GetIsExit()
{
	return b_is_exit;
}

GameState& GameManager::GetGameState()
{
	return *game_state.get();
}

void GameManager::SetUsername(std::string temp)
{
	username = temp;
}

void GameManager::SetPassword(std::string temp)
{
	password = temp;
}

std::string GameManager::GetUsername()
{
	return username;
}

std::string GameManager::GetPassword()
{
	return password;
}

void GameManager::SetScore(int temp)
{
	score = temp;
}

int GameManager::GetScore()
{
	return score;
}

void GameManager::iInit()
{
	game_state = std::make_unique<GameState>();
	game_state->Init();
}

void GameManager::iUpdate()
{
	game_state->UpdateLogic();
}

void GameManager::iShutdown()
{

}
