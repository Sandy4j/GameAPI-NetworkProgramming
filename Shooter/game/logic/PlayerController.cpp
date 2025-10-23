#include <algorithm>
#include <imgui/imgui_impl_glfw.h>

#include "Sprite.h"
#include "RayLine.h"

#include "GameManager.h"
#include "InputManager.h"

#include "PlayerController.h"

PlayerController::PlayerController(Entity& temp_entity, EGameState& temp_state) : 
	entity(temp_entity), current_state(temp_state)
{
	current_select_state = ESelectState::eNone;

	ray_line = new RayLine(temp_entity);

	InsertPosibleGacoMove();
	InsertGacoTrackers();
	InsertWadahGaco();

	InputManager::GetInstance().BindKeyFunction(std::bind(&PlayerController::CloseGame, this), GLFW_KEY_ESCAPE, EInputEventType::ePress, EGameState::eGameplayPlayerOne);
	InputManager::GetInstance().BindKeyFunction(std::bind(&PlayerController::CloseGame, this), GLFW_KEY_ESCAPE, EInputEventType::ePress, EGameState::eGameplayPlayerTwo);
	InputManager::GetInstance().BindMouseFunction(std::bind(&PlayerController::SelectEntity, this), GLFW_MOUSE_BUTTON_1, EInputEventType::ePress, EGameState::eGameplayPlayerOne);
	InputManager::GetInstance().BindMouseFunction(std::bind(&PlayerController::SelectEntity, this), GLFW_MOUSE_BUTTON_1, EInputEventType::ePress, EGameState::eGameplayPlayerTwo);
}

void PlayerController::SetFunctionUpdateState(std::function<void()> temp)
{
	function_update_state = temp;
}

void PlayerController::ResetSelect()
{
	if (id_entity_selected != 0)
	{
		Sprite* sprite = entity.GetComponent<Sprite>(id_entity_selected);
		if (sprite) sprite->ChangeColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	if (id_last != 0)
	{
		Sprite* old_sprite = entity.GetComponent<Sprite>(id_last);
		if (old_sprite) old_sprite->ChangeColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	id_entity_selected = 0;
	id_last = 0;
}

void PlayerController::BindingCallback()
{
	GLFWwindow* window = GameManager::GetInstance().GetWindow();
	ImGui_ImplGlfw_RestoreCallbacks(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
}

void PlayerController::UnBindingCallback()
{
	GLFWwindow* window = GameManager::GetInstance().GetWindow();
	glfwSetWindowUserPointer(window, nullptr);
	std::cout << "unbind" << std::endl;
}

void PlayerController::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    PlayerController* player = static_cast<PlayerController*>(glfwGetWindowUserPointer(window));

    if (!player) return;

    player->MoveCursor();
}

void PlayerController::CloseGame()
{
	/*GameManager::GetInstance().SetIsExit(true);
	glfwSetWindowShouldClose(GameManager::GetInstance().GetWindow(), GLFW_TRUE);*/
	//GameManager::GetInstance().GetGameState().ChangeState(EGameState::ePauseMenu);
	GameManager::GetInstance().GetGameState().ChangeState(EGameState::eMainMenu);
}

void PlayerController::InsertPosibleGacoMove()
{
	std::set<int> temp_index_board;

	temp_index_board.insert(-2);
	temp_index_board.insert(-3);
	temp_index_board.insert(-5);
	posible_gaco_move.insert(std::pair(-1, temp_index_board));

	temp_index_board.clear();
	temp_index_board.insert(-1);
	temp_index_board.insert(-3);
	temp_index_board.insert(-4);
	temp_index_board.insert(-5);
	temp_index_board.insert(-7);
	posible_gaco_move.insert(std::pair(-2, temp_index_board));

	temp_index_board.clear();
	temp_index_board.insert(-1);
	temp_index_board.insert(-2);
	temp_index_board.insert(-5);
	temp_index_board.insert(-6);
	temp_index_board.insert(-7);
	posible_gaco_move.insert(std::pair(-3, temp_index_board));

	temp_index_board.clear();
	temp_index_board.insert(-2);
	temp_index_board.insert(-5);
	temp_index_board.insert(-7);
	posible_gaco_move.insert(std::pair(-4, temp_index_board));

	temp_index_board.clear();
	temp_index_board.insert(-1);
	temp_index_board.insert(-2);
	temp_index_board.insert(-3);
	temp_index_board.insert(-4);
	temp_index_board.insert(-6);
	temp_index_board.insert(-7);
	temp_index_board.insert(-8);
	temp_index_board.insert(-9);
	posible_gaco_move.insert(std::pair(-5, temp_index_board));

	temp_index_board.clear();
	temp_index_board.insert(-3);
	temp_index_board.insert(-5);
	temp_index_board.insert(-8);
	posible_gaco_move.insert(std::pair(-6, temp_index_board));

	temp_index_board.clear();
	temp_index_board.insert(-4);
	temp_index_board.insert(-2);
	temp_index_board.insert(-5);
	temp_index_board.insert(-8);
	temp_index_board.insert(-9);
	posible_gaco_move.insert(std::pair(-7, temp_index_board));

	temp_index_board.clear();
	temp_index_board.insert(-3);
	temp_index_board.insert(-5);
	temp_index_board.insert(-6);
	temp_index_board.insert(-7);
	temp_index_board.insert(-9);
	posible_gaco_move.insert(std::pair(-8, temp_index_board));

	temp_index_board.clear();
	temp_index_board.insert(-5);
	temp_index_board.insert(-7);
	temp_index_board.insert(-8);
	posible_gaco_move.insert(std::pair(-9, temp_index_board));
}

void PlayerController::InsertGacoTrackers()
{
	for (int i = 1; i < 7; i++)
	{
		gaco_trackers.insert(std::pair(i, 0));
	}
}

void PlayerController::MoveCursor()
{
	int current_id = ray_line->ShootRayLine();

	if (current_id == id_last) return;

	if (current_id != 0)
	{
		if (current_id == id_entity_selected) return;

		Sprite* new_sprite = entity.GetComponent<Sprite>(current_id);
		if (new_sprite) new_sprite->ChangeColor(glm::vec3(1.3f, 1.3f, 1.3f));
	}

	if (id_last != 0)
	{
		Sprite* old_sprite = entity.GetComponent<Sprite>(id_last);
		if (old_sprite) old_sprite->ChangeColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	id_last = current_id;

	if (current_select_state != ESelectState::eSelect) return;

	glm::vec3 color = (current_id == id_entity_selected)? glm::vec3(.85f, .85f, .85f) : glm::vec3(.75f, .75f, .75f);

	entity.GetComponent<Sprite>(id_entity_selected)->ChangeColor(color);
}

void PlayerController::SelectEntity()
{
	int temp = ray_line->ShootRayLine();
	std::cout << "shoot ray" << std::endl;

	if (temp == 0) return;

	std::cout << "ID != 0" << std::endl;

	if (current_select_state == ESelectState::eNone)
	{
		if (!entity.GetComponent<Sprite>(temp)) return;

		std::cout << "select entity" << std::endl;
		current_select_state = ESelectState::eSelect;

		id_entity_selected = temp;
		entity.GetComponent<Sprite>(id_entity_selected)->ChangeColor(glm::vec3(.75f, .75f, .75f));

		if (id_entity_selected < 0) return;

		CalculateMoveGaco();

		return;
	}

	current_select_state = (IsPlaceingGaco())? ESelectState::ePlacingGaco : ESelectState::eMoveGaco;

	switch (current_select_state)
	{
	case ESelectState::ePlacingGaco:
		PlaceingGaco(temp);
		break;
	case ESelectState::eMoveGaco:
		MoveGaco(temp);
		break;
	default:
		break;
	}
}

bool PlayerController::IsPlaceingGaco()
{
	if (id_entity_selected > 0) return false;

	for (auto& temp : gaco_trackers)
	{
		if (temp.second == 0)
		{
			return true;
			break;
		}
	}

	return false;
}

void PlayerController::PlaceingGaco(int id)
{
	if (id_entity_selected != id)
	{
		CancelSelect();
		return;
	}

	int start = (current_state == EGameState::eGameplayPlayerOne)? 1 : 4;
	int end = (current_state == EGameState::eGameplayPlayerOne)? 4 : 7;

	for (int i = start; i < end; i++)
	{
		if (entity.GetComponent<Transform>(i)->scale != glm::zero<glm::vec3>()) continue;
		SetPositionGaco(i);
		break;
	}

	UpdateWadahGaco();
	UpdateWindowWadahGaco();
}

void PlayerController::MoveGaco(int id)
{
	if (id >= id_entity_selected)
	{
		CancelSelect();
		return;
	}

	SetPositionGaco(id);
}

void PlayerController::SetPositionGaco(int id)
{
	int board_id = 0;
	int gaco_id = 0;
	gaco_id = (current_select_state == ESelectState::eMoveGaco) ? id_entity_selected : id;
	board_id = (current_select_state == ESelectState::eMoveGaco)? id : id_entity_selected;

	entity.GetComponent<BoundingBox>(board_id)->b_is_trigger = true;

	entity.GetComponent<Transform>(gaco_id)->position = entity.GetComponent<Transform>(board_id)->position;
	entity.GetComponent<Transform>(gaco_id)->position.y += .07f;
	entity.GetComponent<Transform>(gaco_id)->position.z = -1.45f;
	if (current_select_state == ESelectState::ePlacingGaco) entity.GetComponent<Transform>(gaco_id)->scale = glm::vec3(.1f, .1f, .1f);

	entity.GetComponent<Sprite>(gaco_id)->ChangeColor(glm::vec3(1, 1, 1));
	entity.GetComponent<Sprite>(gaco_id)->layer = entity.GetComponent<Sprite>(board_id)->layer - 1;

	gaco_trackers[gaco_id] = board_id;
	CancelSelect();

	function_update_state();
	CheckCollisionBoard();
	UpdateCollisionGaco();
	CheckWinCondition();
}

void PlayerController::CalculateMoveGaco()
{
	int id_board = gaco_trackers[id_entity_selected];

	for (int i = -1; i > -10; i--)
	{
		if (!posible_gaco_move[id_board].contains(i) && !entity.GetComponent<BoundingBox>(i)->b_is_trigger) entity.GetComponent<BoundingBox>(i)->b_is_trigger = true;
	}
}

void PlayerController::CancelSelect()
{
	current_select_state = ESelectState::eNone;
	entity.GetComponent<Sprite>(id_entity_selected)->ChangeColor(glm::vec3(1, 1, 1));
	ResetSelect();
	CheckCollisionBoard();
}

void PlayerController::CheckCollisionBoard()
{
	std::set<int> boards;

	for (const auto& pair : gaco_trackers)
	{
		boards.insert(pair.second);
	}

	for (int i = -1; i > -10; i--)
	{
		if (boards.contains(i))
		{
			entity.GetComponent<BoundingBox>(i)->b_is_trigger = true;
			continue;
		}

		entity.GetComponent<BoundingBox>(i)->b_is_trigger = false;
	}
}

void PlayerController::UpdateCollisionGaco()
{
	for (int i = 1; i < 7; i++)
	{
		if (entity.GetComponent<Transform>(i)->scale == glm::zero<glm::vec3>()) continue;

		entity.GetComponent<BoundingBox>(i)->b_is_trigger = false;
	}

	int start = (current_state == EGameState::eGameplayPlayerOne) ? 4 : 1;
	int end = (current_state == EGameState::eGameplayPlayerOne) ? 7 : 4;

	for (int i = start; i < end; i++)
	{
		if (entity.GetComponent<Transform>(i)->scale == glm::zero<glm::vec3>()) continue;

		entity.GetComponent<BoundingBox>(i)->b_is_trigger = true;
	}
}

void PlayerController::CheckWinCondition()
{
	std::map<int, int> board_state;

	for (const auto& pair : gaco_trackers)
	{
		int gaco_id = pair.first;
		int board_id = pair.second;

		int player_id = 0;

		if (gaco_id >= 1 && gaco_id <= 3) player_id = 1;
		else if (gaco_id >= 4 && gaco_id <= 6) player_id = 2;

		board_state[board_id] = player_id;
	}

	for (const auto& combination : winning_combinations)
	{
		int pos1 = combination[0];
		int pos2 = combination[1];
		int pos3 = combination[2];

		int temp = board_state[pos1];
		if (temp == 0) continue;

		if (board_state[pos2] != temp || board_state[pos3] != temp) continue;

		std::string temp_s = (temp == 1) ? "player 1 menang" : "player 2 menang";
		std::cout << temp_s << std::endl;
		//GameManager::GetInstance().GetGameState().ChangeState(EGameState::eMainMenu);
		GameManager::GetInstance().UpdateResultGame(temp_s);
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eGameOver);
	}
}

void PlayerController::InsertWadahGaco()
{
	wadah_gaco.insert(std::pair(1, 103));
	wadah_gaco.insert(std::pair(2, 104));
	wadah_gaco.insert(std::pair(3, 105));

	wadah_gaco.insert(std::pair(4, 106));
	wadah_gaco.insert(std::pair(5, 107));
	wadah_gaco.insert(std::pair(6, 108));
}

void PlayerController::UpdateWadahGaco()
{
	for (auto& temp : gaco_trackers)
	{
		if (temp.second == 0)
		{
			int id = wadah_gaco[temp.first];
			entity.GetComponent<Transform>(id)->scale = glm::vec3(.25f, .175f, 0.0f);
			continue;
		}

		int id = wadah_gaco[temp.first];
		entity.GetComponent<Transform>(id)->scale = glm::zero<glm::vec3>();
	}

	UpdateWindowWadahGaco();
}

void PlayerController::UpdateWindowWadahGaco()
{
	std::set<int> player_1;
	std::set<int> player_2;

	player_1.insert(gaco_trackers[1]);
	player_1.insert(gaco_trackers[2]);
	player_1.insert(gaco_trackers[3]);

	player_2.insert(gaco_trackers[4]);
	player_2.insert(gaco_trackers[5]);
	player_2.insert(gaco_trackers[6]);

	entity.GetComponent<Transform>(101)->scale = (player_1.contains(0))? glm::vec3(.55f, .55f, 0.0f) : glm::zero<glm::vec3>();
	entity.GetComponent<Transform>(102)->scale = (player_2.contains(0))? glm::vec3(.55f, .55f, 0.0f) : glm::zero<glm::vec3>();
}