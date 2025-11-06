#ifndef MANUKMANAGER_H
#define MANUKMANAGER_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <vector>

#include "Personal.h"

class Entity;
class SpriteSystem;
class ManukInterface;

class ManukManager : public Personal
{
public:
	ManukManager();
	~ManukManager() = default;

private:
	void FindComponents();
	void LoadPrefabs();
	void InitPrefabs(json temp, int index);
	void CreateEntity();

private:
	json prefabs;
	Entity* entity;
	SpriteSystem* sprite_system;
	std::vector<ManukInterface*> manuk_interfaces;

public:
	virtual void IPersonalStart() override;
	virtual void IPersonalUpdate() override;
};

#endif
