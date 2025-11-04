#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <map>
#include <memory>
#include "state.h"

enum class EGameState
{
	eLoby,
	eMainMenu,
	eGameplay,
	ePauseMenu,
	eGameOver,
	eLeaderboard,
	eNone
};

enum class ETrasition
{
	ePrevious,
	eCurrent,
	eNext
};

class GameState
{
public:
	GameState() = default;
	~GameState() = default;

public:
	void Init();
	void UpdateLogic();
	void UpdateRenderObject();
	void UpdateRenderUI();
	void ChangeState(EGameState state);
	state& GetCurrentState();
	EGameState& GetEnumState(ETrasition trasition);

private:
	std::map<EGameState, std::shared_ptr<state>> states;
	state* current_state;
	EGameState eCurrent_enum, ePrevious_enum, eNext_enum;
};

#endif