#include <fstream>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"

#include "ShaderProgram.h"
#include "SpriteSystem.h"
#include "PersonalSystem.h"

#include "FactoryComponents.h"

#include "GameManager.h"

#include "Level.h"

Level::Level(std::string level)
{
    shader_program = new ShaderProgram();

    entity = new Entity();

    std::ifstream file("assets/data_levels/" + level);

    if (!file.is_open())
    {
        std::cerr << "Failed to open level file!\n";
        return;
    }

    try
    {
        file >> data;

        CreateEntity();
        CreateUI();

        std::cout << "LOAD JSON" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "JSON error: " << e.what() << std::endl;
    }

    sprite_system = new SpriteSystem();
    personal_system = new PersonalSystem();
}

Level::~Level()
{
    delete shader_program;
    delete entity;
    delete personal_system;
    delete sprite_system;
}

void Level::LoadLevel(std::string level)
{
    /*std::ifstream file("assets/data_levels/" + level);

    if (!file.is_open()) 
    {
        std::cerr << "Failed to open level file!\n";
        return;
    }

    try 
    {
        file >> data;

        CreateEntity();
        CreateUI();

        std::cout << "LOAD JSON" << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "JSON error: " << e.what() << std::endl;
    }*/

    sprite_system->SpriteBegin();
    personal_system->PersonalStart();
}

void Level::UnloadLevel()
{
    /*delete personal_system;
    personal_system = nullptr;
    delete sprite_system;
    sprite_system = nullptr;*/

    /*for (size_t i = 0; i < id_entitys.size(); i++)
    {
        entity->RemoveComponent<Transform>(id_entitys[i]);
        entity->RemoveComponent<Sprite>(id_entitys[i]);
        entity->RemoveComponent<BoundingBox>(id_entitys[i]);
        entity->RemoveComponent<Personal>(id_entitys[i]);
        entity->RemoveComponent<Button>(id_entitys[i]);
        entity->RemoveComponent<TextBlock>(id_entitys[i]);
        entity->RemoveComponent<TextBox>(id_entitys[i]);
        entity->RemoveComponent<UiTransform>(id_entitys[i]);
    }*/
}

void Level::UpdatePersonalLogic()
{
    personal_system->PersonalUpdate();
}

void Level::UpdateRenderObject()
{
    sprite_system->SpriteUpdate();
}

void Level::UpdateRenderUI()
{
    id_button_click = 0;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin("##InvisibleWindow", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoBackground
    );

    auto& ui_textblock = entity->GetComponentMap<TextBlock>();

    for (auto& var : ui_textblock)
    {
        void* raw = var.second;
        TextBlock* ptr = static_cast<TextBlock*>(raw);
        ptr->Draw();
    }

    auto& ui_textbox = entity->GetComponentMap<TextBox>();

    for (auto& var : ui_textbox)
    {
        int currentId = var.first;
        void* raw = var.second;
        TextBox* ptr = static_cast<TextBox*>(raw);
        ptr->Draw();
    }

    auto& ui_button = entity->GetComponentMap<Button>();

    for (auto& var : ui_button)
    {
        int currentId = var.first;
        void* raw = var.second;
        Button* ptr = static_cast<Button*>(raw);
        ptr->Draw();
        if (ImGui::IsItemClicked()) id_button_click = currentId;
    }

    ImGui::End();
}

Entity* Level::GetEntity()
{
    return entity;
}

ShaderProgram* Level::GetShaderProgram()
{
    return shader_program;
}

PersonalSystem* Level::GetPersonalSystem()
{
    return personal_system;
}

SpriteSystem* Level::GetSpriteSystem()
{
    return sprite_system;
}

int Level::GetButtonID()
{
    int id = id_button_click;
    id_button_click = 0;
    return id;
}

void Level::CreateEntity()
{
    json object = data["Object"];

    for (auto& [name, obj] : object.items())
    {
        int id = obj["id"].get<int>();
        id_entitys.push_back(id);
        std::cout << "Create Entity Object" << std::endl;
        FactoryComponents::CreateObjectComponents(obj, entity);
    }
}

void Level::CreateUI()
{
    json ui = data["UI"];

    for (auto& [name, obj] : ui.items())
    {
        int id = obj["id"].get<int>();
        id_entitys.push_back(id);
        std::cout << "Create Entity Ui" << std::endl;
        FactoryComponents::CreateUiComponents(obj, entity);
    }
}