#include "InputManager.h"

#include "MainMenuState.h"
#include "GameplayState.h"
#include "PauseState.h"
#include "GameOverState.h"

#include <imgui/imgui.h>
#include "GameState.h"

void GameState::Init()
{
	states[EGameState::eMainMenu] = std::make_shared<MainMenuState>();
	states[EGameState::eGameplayPlayerOne] = std::make_shared<GameplayState>();
	states[EGameState::eGameplayPlayerTwo] = states[EGameState::eGameplayPlayerOne];
	states[EGameState::ePauseMenu] = std::make_unique<PauseState>();
	states[EGameState::eGameOver] = std::make_unique<GameOverState>();

	current_state = states[EGameState::eMainMenu].get();
	current_state->iEnter();
	//ChangeState(EGameState::eGameOver);
}

void GameState::UpdateLogic()
{
	current_state->iUpdateLogic();
}

void GameState::UpdateRenderObject()
{
	current_state->iUpdateRenderObject();
}

void GameState::UpdateRenderUI()
{
	current_state->iUpdateRenderUI();
}

void GameState::ChangeState(EGameState state)
{
	ePrevious_enum = eCurrent_enum;
	eNext_enum = state;
	current_state->iExit();
	current_state = states[state].get();
	eCurrent_enum = state;
	current_state->iEnter();
	eNext_enum = EGameState::eNone;
	InputManager::GetInstance().UpdateInputAction();
}

state& GameState::GetCurrentState()
{
	return *current_state;
}

EGameState& GameState::GetEnumState(ETrasition trasition)
{
	switch (trasition)
	{
	case ETrasition::ePrevious:
		return ePrevious_enum;
		break;
	case ETrasition::eCurrent:
		return eCurrent_enum;
		break;
	case ETrasition::eNext:
		return eNext_enum;
		break;
	}
}
