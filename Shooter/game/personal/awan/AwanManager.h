#ifndef AWANMANAGER_H
#define AWANMANAGER_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <vector>

#include "Personal.h"

class Entity;
class SpriteSystem;
class AwanInterface;

class AwanManager : public Personal
{
public:
	AwanManager() = default;
	~AwanManager() = default;

private:
	void FindComponents();
	void LoadPrefabs();
	void InitPrefabs(json temp);
	void CreateEntity();

private:
	json prefabs;
	Entity* entity;
	SpriteSystem* sprite_system;
	std::vector<AwanInterface*> awan_interfaces;

public:
	virtual void IPersonalStart() override;
	virtual void IPersonalUpdate() override;
};

#endif
