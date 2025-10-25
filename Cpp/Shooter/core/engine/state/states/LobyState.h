#ifndef LOBYSTATE_H
#define LOBYSTATE_H

#include "state.h"

class LobyState : public state
{
public:
	LobyState();
	~LobyState() = default;

public:
	virtual void iEnter() override;
	virtual void iUpdateLogic() override;
	virtual void iUpdateRenderObject() override;
	virtual void iUpdateRenderUI() override;
	virtual void iExit() override;

};

#endif
