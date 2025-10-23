#include "Level.h"

#include "Entity.h"
#include "TextBox.h"

#include "GameManager.h"

#include "LobyState.h"

LobyState::LobyState()
{
	level = new Level();
}

void LobyState::iEnter()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ClearInputKeys();

	level->LoadLevel("loby_level.json");
}

void LobyState::iUpdateLogic()
{
	int id = level->GetButtonID();
	bool condition = !level->GetEntity()->GetComponent<TextBox>(2)->input.empty() && !level->GetEntity()->GetComponent<TextBox>(3)->input.empty();

	if (id == 1 && condition)
	{
		GameManager::GetInstance().SetUsername(level->GetEntity()->GetComponent<TextBox>(2)->input);
		GameManager::GetInstance().SetPassword(level->GetEntity()->GetComponent<TextBox>(3)->input);
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eMainMenu);
	}
}

void LobyState::iUpdateRenderObject()
{
	level->UpdateRenderObject();
}

void LobyState::iUpdateRenderUI()
{
	level->UpdateRenderUI();
}

void LobyState::iExit()
{

}
