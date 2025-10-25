#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "state.h"

class GameOverState : public state
{
public:
	GameOverState();
	~GameOverState() = default;

public:
	virtual void iEnter() override;
	virtual void iUpdateLogic() override;
	virtual void iUpdateRenderObject() override;
	virtual void iUpdateRenderUI() override;
	virtual void iExit() override;
};

#endif