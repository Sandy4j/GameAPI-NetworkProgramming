#include <string>
#include <format>

#include "Entity.h"
#include "TextBlock.h"

#include "GameManager.h"
#include "TimeManager.h"

#include "Level.h"

#include "Timer.h"

void Timer::StartTimer(float time)
{
	max_time = time;
	current_time = max_time;
	b_is_running = true;
}

void Timer::StopTimer()
{
	b_is_running = false;
}

void Timer::ChangeState()
{
	if (current_time > 0) return;

	b_is_running = false;
	GameManager::GetInstance().GetGameState().ChangeState(EGameState::eGameOver);
}

void Timer::IPersonalStart()
{
	Level* level = GameManager::GetInstance().GetLevel();
	Entity* entity = level->GetEntity();
	timer_text = entity->GetComponent<TextBlock>(4);
}

void Timer::IPersonalUpdate()
{
	if (!b_is_running) return;

	current_time -= TimeManager::GetInstance().GetDeltaTime();

	int total_seconds = static_cast<int>(std::max(0.0f, current_time));
	int seconds = total_seconds % 60;
	std::string time_format = std::format("{:02}", seconds);

	timer_text->label = "timer: " + time_format;

	ChangeState();
}
