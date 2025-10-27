#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

class Level;
class GunSystem;

class PlayerController
{
public:
	PlayerController();
	~PlayerController() = default;

public:
	void Enter();
	void UpdatePlayerController();

private:
	void Pause();

private:
	GunSystem* gun_system;
};

#endif
