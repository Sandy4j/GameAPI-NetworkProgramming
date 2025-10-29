#include <iostream>
#include <format>

#include "Entity.h"
#include "TextBlock.h"

#include "GameManager.h"
#include "TimeManager.h"

#include "Level.h"

#include "Timer.h"

void Timer::StartTimer()
{
	timer_text = GameManager::GetInstance().GetLevel()->GetEntity()->GetComponent<TextBlock>(4);
	b_is_runing = true;
	current_duration = 0;
	current_duration = duration_timer;
}

void Timer::NewTimer(float timer)
{
	duration_timer = timer;
}

void Timer::IPersonalStart()
{

}

void Timer::IPersonalUpdate()
{
	if (!b_is_runing) return;

	current_duration -= TimeManager::GetInstance().GetDeltaTime();

	int total_seconds = static_cast<int>(std::max(0.0f, current_duration));
	int seconds = total_seconds % 60;
	std::string time_format = std::format("{:02}", seconds);

	timer_text->label = time_format;

	if (seconds != 0) return;

	b_is_runing = false;
	GameManager::GetInstance().GetGameState().ChangeState(EGameState::eGameOver);
}
