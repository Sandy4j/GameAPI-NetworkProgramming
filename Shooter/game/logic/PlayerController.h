#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Entity.h"

class Level;
class GunSystem;

class PlayerController
{
public:
	PlayerController(Entity& temp_entity, Level& temp_level);
	~PlayerController() = default;

public:
	void UpdatePlayerController();

private:
	void Pause();

private:
	Entity& entity;
	//RayLine* ray_line;
	GunSystem* gun_system;
};

#endif
