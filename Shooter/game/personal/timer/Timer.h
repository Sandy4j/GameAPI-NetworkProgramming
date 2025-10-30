#ifndef TIMER_H
#define TIMER_H

#include "Personal.h"

struct TextBlock;

class Timer : public Personal
{
public:
	Timer() = default;
	~Timer() = default;

public:
	void StartTimer(float time);
	void StopTimer();

private:
	void ChangeState();

private:
	bool b_is_running;
	float current_time, max_time;
	TextBlock* timer_text;

public:
	virtual void IPersonalStart() override;
	virtual void IPersonalUpdate() override;
};

#endif
