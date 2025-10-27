#ifndef LEVEL_H
#define LEVEL_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "TextBlock.h"
#include "TextBox.h"
#include "Button.h"

class ShaderProgram;
class Entity;
class SpriteSystem;
class PersonalSystem;

class Level
{
public:
    Level();
    ~Level();

public:
	void LoadLevel(std::string level);
    void UpdatePersonalLogic();
    void UpdateRenderObject();
	void UpdateRenderUI();

    Entity* GetEntity();
    ShaderProgram* GetShaderProgram();
    PersonalSystem* GetPersonalSystem();
    SpriteSystem* GetSpriteSystem();

    int GetButtonID();

private:
    void CreateEntity();
    void CreateUI();

private:
    json data;

    ShaderProgram* shader_program;

    Entity* entity;
    PersonalSystem* personal_system;
    SpriteSystem* sprite_system;

    int id_button_click;

};

#endif