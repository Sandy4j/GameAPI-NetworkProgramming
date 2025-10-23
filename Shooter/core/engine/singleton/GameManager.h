#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <memory>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "singleton.h"
#include "GameState.h"
#include <string>

class TurnTimer;

class GameManager : public singleton<GameManager>
{
public:
	GameManager() = default;
	~GameManager() = default;

public:
	void CreateMainWindow(float x, float y);
	GLFWwindow* GetWindow();
	glm::vec2& GetSizeWindow();
	glm::vec2& GetMousePosition();
	void SetIsExit(bool value);
	bool GetIsExit();

	GameState& GetGameState();

	void UpdateResultGame(std::string temp);
	std::string GetResultGame();

private:
	GLFWwindow* window;
	glm::vec2* size_window;
	glm::vec2* mouse_position;
	bool b_is_exit;

	std::unique_ptr<GameState> game_state;

	std::string result_game;

public:
	virtual void iInit() override;
	virtual void iUpdate() override;
	virtual void iShutdown() override;
};

#endif