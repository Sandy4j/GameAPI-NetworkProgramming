#ifndef FACTORYCOMPONENTS_H
#define FACTORYCOMPONENTS_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "TextBlock.h"
#include "TextBox.h"
#include "Button.h"

#include "EnemyManager.h"
#include "Timer.h"

class FactoryComponents
{
public:
    static void CreateObjectComponents(const auto& obj, Entity* entity)
    {
        int id = obj["id"].get<int>();
        int layer = obj["layer"].get<int>();
        auto& components = obj["components"];

        if (components.contains("transform"))
        {
            auto& val = components["transform"];
            Transform* temp = new Transform();
            temp->position = glm::vec3(val["position"][0].get<float>(), val["position"][1].get<float>(), val["position"][2].get<float>());
            //temp->rotation = val["rotation"][0].get<float>();
            temp->rotation = glm::vec2(val["rotation"][0].get<float>(), val["rotation"][1].get<float>());
            temp->scale = glm::vec3(val["scale"][0].get<float>(), val["scale"][1].get<float>(), val["scale"][2].get<float>());
            entity->AddComponent<Transform>(id, temp);
        }

        if (components.contains("sprite"))
        {
            auto& val = components["sprite"];
            Sprite* temp = new Sprite();
            temp->layer = layer;
            temp->location_vertex = obj["shaders"]["vertex"].get<std::string>();
            temp->location_fragment = obj["shaders"]["fragment"].get<std::string>();
            temp->ChangeColor(glm::vec3(val["color"][0].get<float>(), val["color"][1].get<float>(), val["color"][2].get<float>()));
            for (auto& image_path : val["image"])
            {
                temp->location_textures.push_back(image_path.get<std::string>());
            }
            temp->transform = entity->GetComponent<Transform>(id);
            entity->AddComponent<Sprite>(id, temp);
        }

        if (components.contains("bounding_box"))
        {
            auto& val = components["bounding_box"];
            BoundingBox* temp = new BoundingBox();
            temp->b_is_trigger = val["is_trigger"];
            entity->AddComponent<BoundingBox>(id, temp);
        }

        if (components.contains("personal"))
        {
            auto& val = components["personal"];

            if (val["script_personal"] == "enemy_manager")
            {
                Personal* temp = new EnemnyManager();
                entity->AddComponent<Personal>(id, temp);
            }

            if (val["script_personal"] == "timer")
            {
                Personal* temp = new Timer();
                entity->AddComponent<Personal>(id, temp);
            }
        }
    }

    static void CreateUiComponents(const auto& obj, Entity* entity)
    {
        int id = obj["id"].get<int>();
        auto& components = obj["components"];
        glm::vec2 position = glm::vec2(0, 0);
        glm::vec2 scale = glm::vec2(0, 0);

        if (components.contains("transform"))
        {
            auto& val = components["transform"];
            position = glm::vec2(val["position"][0].get<float>(), val["position"][1].get<float>());
            scale = glm::vec2(val["scale"][0].get<float>(), val["scale"][1].get<float>());
        }

        if (components.contains("textblock"))
        {
            auto& val = components["textblock"];
            TextBlock* temp = new TextBlock();
            temp->label = val["label"].get<std::string>();
            temp->position = position;
            temp->size = scale.x;
            entity->AddComponent<TextBlock>(id, temp);
        }

        if (components.contains("textbox"))
        {
            auto& val = components["textbox"];
            TextBox* temp = new TextBox();
            temp->label = val["label"].get<std::string>();
            temp->position = position;
            temp->size = scale.x;
            entity->AddComponent<TextBox>(id, temp);
        }

        if (components.contains("button"))
        {
            auto& val = components["button"];
            Button* temp = new Button();
            temp->label = val["label"].get<std::string>();
            temp->position = position;
            temp->size = scale;
            entity->AddComponent<Button>(id, temp);
        }
    }

    static int InstantiatePrefab(json& file, Entity* entity, glm::vec3 pos, glm::vec2 rot, glm::vec3 scale)
    {
        int id = entity->GetLastID() + 1;

        for (auto& [name, obj] : file.items())
        {
            int layer = obj["layer"].get<int>();
            auto& components = obj["components"];

            if (components.contains("transform"))
            {
                auto& val = components["transform"];
                Transform* temp = new Transform();
                temp->position = pos;
                //temp->rotation = rot;
                temp->rotation = rot;
                temp->scale = scale;
                entity->AddComponent<Transform>(id, temp);
            }

            if (components.contains("sprite"))
            {
                auto& val = components["sprite"];
                Sprite* temp = new Sprite();
                temp->layer = layer;
                temp->location_vertex = obj["shaders"]["vertex"].get<std::string>();
                temp->location_fragment = obj["shaders"]["fragment"].get<std::string>();
                temp->ChangeColor(glm::vec3(val["color"][0].get<float>(), val["color"][1].get<float>(), val["color"][2].get<float>()));
                for (auto& image_path : val["image"])
                {
                    temp->location_textures.push_back(image_path.get<std::string>());
                }
                temp->transform = entity->GetComponent<Transform>(id);
                entity->AddComponent<Sprite>(id, temp);
            }

            if (components.contains("bounding_box"))
            {
                auto& val = components["bounding_box"];
                BoundingBox* temp = new BoundingBox();
                temp->b_is_trigger = val["is_trigger"];
                entity->AddComponent<BoundingBox>(id, temp);
            }

            if (components.contains("personal"))
            {
                auto& val = components["personal"];

                if (val["script_personal"] == "enemy_manager")
                {
                    Personal* temp = new EnemnyManager();
                    entity->AddComponent<Personal>(id, temp);
                }

                if (val["script_personal"] == "timer")
                {
                    Personal* temp = new Timer();
                    entity->AddComponent<Personal>(id, temp);
                }
            }
        }

        return id;
    }
};

#endif