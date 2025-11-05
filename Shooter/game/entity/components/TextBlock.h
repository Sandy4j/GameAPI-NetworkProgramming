#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include <string>
#include <imgui/imgui.h>
#include "UiTransform.h"

struct TextBlock
{
public:
    UiTransform* transform;
    std::string label;

public:
    void Draw()
    {
        if (!transform->b_is_active) return;

        float base = 16.0f;
        float scale = transform->scale.x * (base / 100.0f);

        ImGui::SetCursorPos(ImVec2(transform->position.x, transform->position.y));
        ImGui::SetWindowFontScale(scale);
        ImGui::Text(label.c_str());
        ImGui::SetWindowFontScale(1);
    }
};

#endif