#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "state.h"

class PauseState : public state
{
public:
	PauseState();
	~PauseState() = default;

private:
	void UnPause();

public:
	virtual void iEnter() override;
	virtual void iUpdateLogic() override;
	virtual void iUpdateRenderObject() override;
	virtual void iUpdateRenderUI() override;
	virtual void iExit() override;
};

#endif