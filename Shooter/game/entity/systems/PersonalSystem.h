#ifndef PERSONALSYSTEM_H
#define PERSONALSYSTEM_H

#include <vector>

class Personal;
class Entity;

class PersonalSystem
{
public:
	PersonalSystem() = default;
	~PersonalSystem() = default;

public:
	void PersonalStart();
	void PersonalUpdate();

private:
	Entity* entity;
};

#endif
