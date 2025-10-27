#ifndef STATE_H
#define STATE_H

class Level;

class state
{
protected:
	state() = default;

public:
	virtual ~state();

protected:
	Level* level;

public:
	virtual void iEnter() = 0;
	virtual void iUpdateLogic() = 0;
	virtual void iUpdateRenderObject() = 0;
	virtual void iUpdateRenderUI() = 0;
	virtual void iExit() = 0;
};

#endif