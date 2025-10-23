#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <set>
#include <functional>

#include "Entity.h"

enum class EGameState : int;
class RayLine;
struct GLFWwindow;

enum class ESelectState
{
	eNone,
	eSelect,
	ePlacingGaco,
	eMoveGaco
};

class PlayerController
{
public:
	PlayerController(Entity& temp_entity, EGameState& temp_state);

	~PlayerController() = default;

public:
	void SetFunctionUpdateState(std::function<void()> temp);
	void ResetSelect();
	void BindingCallback();
	void UnBindingCallback();

private:
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	void CloseGame();

	void InsertPosibleGacoMove();
	void InsertGacoTrackers();
	void MoveCursor();
	void SelectEntity();
	bool IsPlaceingGaco();
	void PlaceingGaco(int id);
	void MoveGaco(int id);
	void SetPositionGaco(int id);
	void CalculateMoveGaco();
	void CancelSelect();
	void CheckCollisionBoard();
	void UpdateCollisionGaco();
	void CheckWinCondition();

	void InsertWadahGaco();
	void UpdateWadahGaco();
	void UpdateWindowWadahGaco();

private:
	ESelectState current_select_state;

	std::function<void()> function_update_state;
	EGameState& current_state;

	Entity& entity;
	RayLine* ray_line;

	int id_last;
	int id_entity_selected;
	std::map<int, int> gaco_trackers;
	std::map<int, std::set<int>> posible_gaco_move;

	std::map<int, int> wadah_gaco;

	const std::vector<std::vector<int>> winning_combinations = 
	{
		{-1, -2, -4}, {-3, -5, -7}, {-6, -8, -9},
		{-1, -3, -6}, {-2, -5, -8}, {-4, -7, -9},
		{-1, -5, -9}, {-4, -5, -6}
	};
};

#endif
