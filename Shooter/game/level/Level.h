#ifndef LEVEL_H
#define LEVEL_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "TextBlock.h"
#include "Button.h"

class ShaderProgram;
class Entity;
class SpriteSystem;

class Level
{
public:
    Level();
	~Level() = default;

public:
	void LoadLevel(std::string level);
    void UpdateRenderObject();
	void UpdateRenderUI();

    Entity* GetEntity();
    SpriteSystem* GetSpriteSystem();

    int GetButtonID();

private:
    void CreateEntity();
    void CreateUI();

private:
    json data;

    ShaderProgram* shader_program;

    Entity* entity;
    SpriteSystem* sprite_system;

    int id_button_click;

};

#endif