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

        float finalWidth = 150 * transform->scale.x;
        float finalHeight = 50 * transform->scale.y;
        float fontScale = finalHeight / 100.0f / 2;

        ImGui::PushItemWidth(finalWidth);
        ImGui::SetWindowFontScale(fontScale);
        ImGui::SetCursorPos(ImVec2(transform->position.x, transform->position.y));
        ImGui::Button(label.c_str(), ImVec2(finalWidth, finalHeight));
        ImGui::SetWindowFontScale(1.0f);
    }
};

#endif
