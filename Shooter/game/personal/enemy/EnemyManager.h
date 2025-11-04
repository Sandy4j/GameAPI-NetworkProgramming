#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>

#include "Personal.h"

class SpriteSystem;
class EnemyInterface;
class Entity;
class Timer;

enum class EState
{
	GameplayState,
	TransitionState
};

class EnemyManager : public Personal
{
public:
	EnemyManager() = default;
	~EnemyManager() = default;

private:
	void Init();
	void LoadPrefabs();
	void FindComponent();
	void CreateEntity();
	void InitPrefabs(json temp);
	int RandomNumber(int min, int max);
	float RandomNumberFloat(float min, float max);
	void StartWaveEnemy();
	void ResetWaveEnemy();
	void CheckWaveCondition();
	bool StateCondition();

private:
	EState current_state;

	json prefabs;

	Entity* entity;
	SpriteSystem* sprite_system;
	Timer* timer;

	std::vector<EnemyInterface*> enemys, enemy_pools;
	std::string ikan_paths[4];

	int start_enemy, total_enemy;
	bool b_is_reset;

	float transition_delay;

public:
	virtual void IPersonalStart() override;
	virtual void IPersonalUpdate() override;
};

#endif
