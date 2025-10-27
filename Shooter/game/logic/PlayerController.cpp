#include <algorithm>
#include <imgui/imgui_impl_glfw.h>

#include "Sprite.h"
#include "TextBlock.h"
#include "RayLine.h"
//#include "Level.h"

#include "GameManager.h"
#include "InputManager.h"

#include "GunSystem.h"

#include "PlayerController.h"

PlayerController::PlayerController()
{
	gun_system = new GunSystem();

	InputManager::GetInstance().BindKeyFunction(std::bind(&PlayerController::Pause, this), GLFW_KEY_ESCAPE, EInputEventType::ePress, EGameState::eGameplay);
}

void PlayerController::Enter()
{
	gun_system->Enter();
}

void PlayerController::UpdatePlayerController()
{
	gun_system->UpdateGunSystem();
}

void PlayerController::Pause()
{
	GameManager::GetInstance().GetGameState().ChangeState(EGameState::ePauseMenu);
}
