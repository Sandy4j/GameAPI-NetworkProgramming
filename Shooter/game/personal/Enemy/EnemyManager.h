#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <vector>

#include "Personal.h"

class EnemySystem;
class Entity;

class EnemnyManager : public Personal
{
public:
	EnemnyManager() = default;
	~EnemnyManager() = default;

private:
	void LoadPrefabs();
	void CreateEntity();

private:
	json prefabs;

	std::vector<EnemySystem*> enemys;
	Entity* entity;

public:
	virtual void IPersonalStart() override;
	virtual void IPersonalUpdate() override;
};

#endif
