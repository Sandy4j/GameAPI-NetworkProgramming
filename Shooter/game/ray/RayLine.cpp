#include <iostream>
#include <algorithm>

#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"

#include "GameManager.h"
#include "RenderManager.h"

#include "Level.h"

#include "RayLine.h"

int RayLine::ShootRayLine()
{
    Level* level = GameManager::GetInstance().GetLevel();
    Entity* entity = level->GetEntity();

    glm::mat4 projectionMatrix = RenderManager::GetInstance().GetProjectionMatrix();
    glm::mat4 viewMatrix = RenderManager::GetInstance().GetViewMatrix();
    glm::vec3 cameraPosition = glm::vec3(glm::inverse(viewMatrix)[3]);

    glm::vec3 ray_dir = CalculateRayLine(projectionMatrix, viewMatrix);

    float closest_distance = FLT_MAX;
    int id_hit_entity = 0;

    //auto& component = entity.GetComponentMap<Sprite>();
    auto& component = entity->GetComponentMap<Sprite>();
    std::vector<std::pair<int, Sprite*>> sprites;

    for (auto& pair : component) 
    {
        sprites.push_back({ pair.first, static_cast<Sprite*>(pair.second) });
    }

    std::sort(sprites.begin(), sprites.end(), [](const auto& a, const auto& b) 
        {
            return a.second->layer < b.second->layer;
        }
    );

    for (auto& obj : sprites)
    {
        int entity_id = obj.first;
        /*Transform* transform = entity.GetComponent<Transform>(entity_id);
        BoundingBox* bounding_box = entity.GetComponent<BoundingBox>(entity_id);*/
        Transform* transform = entity->GetComponent<Transform>(entity_id);
        BoundingBox* bounding_box = entity->GetComponent<BoundingBox>(entity_id);

        if (!bounding_box || bounding_box->b_is_trigger) continue;

        glm::vec3 scaled_min = bounding_box->min * transform->scale;
        glm::vec3 scaled_max = bounding_box->max * transform->scale;

        glm::vec3 world_box_min = scaled_min + transform->position;
        glm::vec3 world_box_max = scaled_max + transform->position;

        float distance;

        if (!CheckRayAABBIntersection(cameraPosition, ray_dir, world_box_min, world_box_max, distance)) continue;

        if (distance > closest_distance) continue;

        closest_distance = distance;
        id_hit_entity = entity_id;

        break;
    }

    return id_hit_entity;
}

glm::vec3 RayLine::CalculateRayLine(const glm::mat4& projection, const glm::mat4& view)
{
    double mouseX, mouseY;
    int width, height;

    mouseX = GameManager::GetInstance().GetMousePosition().x;
    mouseY = GameManager::GetInstance().GetMousePosition().y;

    width = GameManager::GetInstance().GetSizeWindow().x;
    height = GameManager::GetInstance().GetSizeWindow().y;

    float x = (2.0f * mouseX) / width - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / height;
    float z = 1.0f;
    glm::vec3 ray_nds(x, y, z);

    glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

    glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

    glm::vec3 ray_world = glm::vec3(glm::inverse(view) * ray_eye);
    ray_world = glm::normalize(ray_world);

    return ray_world;
}

bool RayLine::CheckRayAABBIntersection(const glm::vec3& ray_origin, const glm::vec3& ray_direction, const glm::vec3& box_min, const glm::vec3& box_max, float& distance)
{
    glm::vec3 inv_dir = 1.0f / ray_direction;

    float t1 = (box_min.x - ray_origin.x) * inv_dir.x;
    float t2 = (box_max.x - ray_origin.x) * inv_dir.x;
    float t3 = (box_min.y - ray_origin.y) * inv_dir.y;
    float t4 = (box_max.y - ray_origin.y) * inv_dir.y;
    float t5 = (box_min.z - ray_origin.z) * inv_dir.z;
    float t6 = (box_max.z - ray_origin.z) * inv_dir.z;

    float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));

    float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

    if (tmax < 0) 
    {
        distance = tmax;
        return false;
    }

    if (tmin > tmax) 
    {
        distance = tmax;
        return false;
    }

    distance = tmin;
    return true;
}
