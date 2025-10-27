#ifndef SPRITESYSTEM_H
#define SPRITESYSTEM_H

#include "Sprite.h"

class Entity;

class SpriteSystem
{
public:
	SpriteSystem();
	~SpriteSystem() = default;

public:
	void SpriteBegin();
	void SpriteUpdate();
	void ReorderRender();

private:
	void RenderQueue();

public:
	ShaderProgram* shader_program;
	Entity* entity;

	std::vector<Sprite*> sprites;
};

#endif
