#ifndef GUNSYSTEM_H
#define GUNSYSTEM_H

//#include "Entity.h"
//#include "Level.h"
class Level;
class RayLine;

class GunSystem
{
public:
	GunSystem();
	~GunSystem() = default;

public:
	void Enter();
	void UpdateGunSystem();

private:
	void Reload();
	bool IsCanFire();
	void Fire();

private:
	Entity* entity;
	Level* level;
	RayLine* ray_line;

	int current_ammo, max_ammo;
	float reload_time;
	bool b_is_reload;

};

#endif
