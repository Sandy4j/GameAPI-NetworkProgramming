#include <algorithm>
#include <imgui/imgui_impl_glfw.h>

#include "Sprite.h"
#include "TextBlock.h"
#include "RayLine.h"

#include "GameManager.h"
#include "InputManager.h"

#include "Level.h"
#include "GunSystem.h"

#include "PlayerController.h"

PlayerController::PlayerController(Entity& temp_entity, Level& temp_level) : 
	entity(temp_entity)
{
	gun_system = new GunSystem(temp_entity, temp_level);

	InputManager::GetInstance().BindKeyFunction(std::bind(&PlayerController::Pause, this), GLFW_KEY_ESCAPE, EInputEventType::ePress, EGameState::eGameplay);
}

void PlayerController::UpdatePlayerController()
{
	gun_system->UpdateGunSystem();
}

void PlayerController::Pause()
{
	GameManager::GetInstance().GetGameState().ChangeState(EGameState::ePauseMenu);
}
