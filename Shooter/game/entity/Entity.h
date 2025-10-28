#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <unordered_set>
#include <typeindex>

class Entity
{
public:
    Entity() = default;
    ~Entity()
    {
        for (auto& [type, componentMap] : components)
        {
            for (auto& [id, componentPtr] : componentMap)
            {
                operator delete(componentPtr);
            }
        }
    }

public:
    template<typename T>
    void AddComponent(int entity, T* component) 
    {
        components[typeid(T)][entity] = component;
    }

    template<typename T>
    T* GetComponent(int entity) 
    {
        auto& compMap = components[typeid(T)];
        if (compMap.find(entity) != compMap.end())
            return static_cast<T*>(compMap[entity]);

        return nullptr;
    }

    template<typename T>
    std::unordered_map<int, void*>& GetComponentMap() 
    {
        return components[typeid(T)];
    }

    int GetLastID()
    {
        int current_ID = 0;
        for (const auto& typePair : components)
        {
            const auto& innerMap = typePair.second;
            for (const auto& entityPair : innerMap)
            {
                current_ID = std::max(current_ID, entityPair.first);
            }
        }

        return current_ID;
    }

private:
    std::unordered_map<std::type_index, std::unordered_map<int, void*>> components;
};

#endif