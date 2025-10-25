#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include "singleton.h"

class TimeManager : public singleton<TimeManager>
{
public:
	TimeManager() = default;
	~TimeManager() = default;

public:
	float& GetDeltaTime();

private:
	void CalculateDeltaTime();

private:
	float delta_time;
	float last_delta_time;

public:
	virtual void iInit() override;
	virtual void iUpdate() override;
	virtual void iShutdown() override;
};

#endif