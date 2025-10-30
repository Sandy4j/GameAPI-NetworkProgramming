#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>

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
	int RandomNumber(int min, int max);

private:
	json prefabs;

	Entity* entity;
	std::vector<EnemySystem*> enemys;
	std::string ikan_paths[4];

public:
	virtual void IPersonalStart() override;
	virtual void IPersonalUpdate() override;
};

#endif
