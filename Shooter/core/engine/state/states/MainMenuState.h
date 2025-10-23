#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state.h"

class MainMenuState : public state
{
public:
	MainMenuState();
	~MainMenuState() = default;

public:
	virtual void iEnter() override;
	virtual void iUpdateLogic() override;
	virtual void iUpdateRenderObject() override;
	virtual void iUpdateRenderUI() override;
	virtual void iExit() override;
};

#endif