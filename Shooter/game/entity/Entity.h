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

private:
    std::unordered_map<std::type_index, std::unordered_map<int, void*>> components;
};

#endif