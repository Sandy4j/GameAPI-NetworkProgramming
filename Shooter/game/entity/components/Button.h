#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <imgui/imgui.h>
#include "UiTransform.h"

struct Button
{
public:
    UiTransform* transform;
    std::string label;

public:
    void Draw()
    {
        if (!transform->b_is_active) return;

        ImGui::SetCursorPos(ImVec2(transform->position.x, transform->position.y));
        ImGui::Button(label.c_str(), ImVec2(transform->scale.x, transform->scale.y));
    }
};

#endif
