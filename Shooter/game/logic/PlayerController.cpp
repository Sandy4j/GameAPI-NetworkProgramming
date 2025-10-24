#include <algorithm>
#include <imgui/imgui_impl_glfw.h>

#include "Sprite.h"
#include "TextBlock.h"
#include "RayLine.h"

#include "GameManager.h"
#include "InputManager.h"

#include "PlayerController.h"

PlayerController::PlayerController(Entity& temp_entity) : 
	entity(temp_entity)
{
	InputManager* input = &InputManager::GetInstance();

	input->BindMouseFunction(std::bind(&PlayerController::Shoot, this), GLFW_MOUSE_BUTTON_1, EInputEventType::ePress, EGameState::eGameplay);
	input->BindKeyFunction(std::bind(&PlayerController::Pause, this), GLFW_KEY_ESCAPE, EInputEventType::ePress, EGameState::eGameplay);
}

void PlayerController::Shoot()
{
	int score = GameManager::GetInstance().GetScore() + 1;
	GameManager::GetInstance().SetScore(score);
	std::cout << "shoot : ";
	std::cout << score << std::endl;
	entity.GetComponent<TextBlock>(2)->label = "score: " + std::to_string(GameManager::GetInstance().GetScore());
}

void PlayerController::Pause()
{
	GameManager::GetInstance().GetGameState().ChangeState(EGameState::ePauseMenu);
}
