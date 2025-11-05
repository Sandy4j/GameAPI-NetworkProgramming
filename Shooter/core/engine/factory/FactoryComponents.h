#ifndef FACTORYCOMPONENTS_H
#define FACTORYCOMPONENTS_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Entity.h"
#include "Transform.h"
#include "UiTransform.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "TextBlock.h"
#include "TextBox.h"
#include "Button.h"
#include "Image.h"

#include "EnemyManager.h"
#include "Timer.h"
#include "AwanManager.h"
#include "ManukManager.h"

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
            temp->b_is_active = val["echo"];
            temp->position = glm::vec3(val["position"][0].get<float>(), val["position"][1].get<float>(), val["position"][2].get<float>());
            temp->rotation = glm::vec2(val["rotation"][0].get<float>(), val["rotation"][1].get<float>());
            temp->scale = glm::vec3(val["scale"][0].get<float>(), val["scale"][1].get<float>(), val["scale"][2].get<float>());
            temp->tag = val["tag"];
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
                Personal* temp = new EnemyManager();
                entity->AddComponent<Personal>(id, temp);
            }

            if (val["script_personal"] == "timer")
            {
                Personal* temp = new Timer();
                entity->AddComponent<Personal>(id, temp);
            }

            if (val["script_personal"] == "awan_manager")
            {
                Personal* temp = new AwanManager();
                entity->AddComponent<Personal>(id, temp);
            }

            if (val["script_personal"] == "manuk_manager")
            {
                Personal* temp = new ManukManager();
                entity->AddComponent<Personal>(id, temp);
            }
        }
    }

    static void CreateUiComponents(const auto& obj, Entity* entity)
    {
        int id = obj["id"].get<int>();
        auto& components = obj["components"];

        if (components.contains("transform"))
        {
            auto& val = components["transform"];
            UiTransform* temp = new UiTransform();
            temp->b_is_active = val["echo"];
            temp->position = glm::vec3(val["position"][0].get<float>(), val["position"][1].get<float>(), val["position"][2].get<float>());
            temp->scale = glm::vec3(val["scale"][0].get<float>(), val["scale"][1].get<float>(), val["scale"][2].get<float>());
            entity->AddComponent<UiTransform>(id, temp);
        }

        if (components.contains("textblock"))
        {
            auto& val = components["textblock"];
            TextBlock* temp = new TextBlock();
            temp->label = val["label"].get<std::string>();
            temp->transform = entity->GetComponent<UiTransform>(id);
            entity->AddComponent<TextBlock>(id, temp);
        }

        if (components.contains("textbox"))
        {
            auto& val = components["textbox"];
            TextBox* temp = new TextBox();
            temp->label = val["label"].get<std::string>();
            temp->transform = entity->GetComponent<UiTransform>(id);
            entity->AddComponent<TextBox>(id, temp);
        }

        if (components.contains("button"))
        {
            auto& val = components["button"];
            Button* temp = new Button();
            temp->label = val["label"].get<std::string>();
            temp->transform = entity->GetComponent<UiTransform>(id);
            entity->AddComponent<Button>(id, temp);
        }

        if (components.contains("image"))
        {
            auto& val = components["image"];
            Image* temp = new Image();
            std::string file = val["texture"].get<std::string>();
            temp->textureID = LoadTexture(file.c_str());
            std::cout << "Path: " << file << " --- Loaded Texture ID: " << temp->textureID << std::endl;
            temp->transform = entity->GetComponent<UiTransform>(id);
            entity->AddComponent<Image>(id, temp);
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
                temp->b_is_active = val["echo"];
                temp->position = pos;
                temp->rotation = rot;
                temp->scale = scale;
                temp->tag = val["tag"];
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
                    Personal* temp = new EnemyManager();
                    entity->AddComponent<Personal>(id, temp);
                }

                if (val["script_personal"] == "timer")
                {
                    Personal* temp = new Timer();
                    entity->AddComponent<Personal>(id, temp);
                }

                if (val["script_personal"] == "awan_manager")
                {
                    Personal* temp = new AwanManager();
                    entity->AddComponent<Personal>(id, temp);
                }

                if (val["script_personal"] == "manuk_manager")
                {
                    Personal* temp = new ManukManager();
                    entity->AddComponent<Personal>(id, temp);
                }
            }
        }

        return id;
    }

    static GLuint LoadTexture(const char* filePath)
    {
        GLuint textureID = 0;
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, STBI_rgb_alpha);

        if (data)
        {
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        }
        else
        {
            std::cerr << "Gagal load tekstur: " << filePath << std::endl;
            std::cerr << "Alasan STB: " << stbi_failure_reason() << std::endl;
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        return textureID;
    }
};

#endif