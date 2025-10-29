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
	void StartTimer();
	void NewTimer(float timer);

private:
	bool b_is_runing;
	float duration_timer, current_duration;
	TextBlock* timer_text;

public:
	virtual void IPersonalStart() override;
	virtual void IPersonalUpdate() override;
};

#endif
