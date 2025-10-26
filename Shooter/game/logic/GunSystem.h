#ifndef GUNSYSTEM_H
#define GUNSYSTEM_H

#include "Entity.h"
class Level;
class RayLine;

class GunSystem
{
public:
	GunSystem(Entity& temp_entity, Level& temp_level);
	~GunSystem() = default;

public:
	void UpdateGunSystem();

private:
	void Reload();
	bool IsCanFire();
	void Fire();

private:
	Level& level;
	Entity& entity;
	RayLine* ray_line;

	int current_ammo, max_ammo;
	float reload_time;
	bool b_is_reload;

};

#endif
