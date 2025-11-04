#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "state.h"

class GLFWcursor;
class PlayerController;
class TurnTimer;
class RayLine;

class GameplayState : public state
{
public:
	GameplayState();
	~GameplayState() = default;

private:
	GLFWcursor* cursor;
	PlayerController* player_controller;

public:
	virtual void iEnter() override;
	virtual void iUpdateLogic() override;
	virtual void iUpdateRenderObject() override;
	virtual void iUpdateRenderUI() override;
	virtual void iExit() override;
};

#endif