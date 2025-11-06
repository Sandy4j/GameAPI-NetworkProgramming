#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>
#include <imgui/imgui.h>
#include "UiTransform.h"

struct TextBox
{
public:
    UiTransform* transform;
    std::string label;
    std::string input;

public:
    void Draw()
    {
        if (!transform->b_is_active) return;

        float finalWidth = 300 * transform->scale.x;
        float finalHeight = 50 * transform->scale.y;
        float fontScale = finalHeight / 100.0f;

        ImGui::SetCursorPos(ImVec2(transform->position.x, transform->position.y));
        ImGui::PushItemWidth(finalWidth);
        ImGui::SetWindowFontScale(fontScale);

        const size_t bufferSize = 256;
        char tempBuffer[bufferSize];
        strncpy_s(tempBuffer, sizeof(tempBuffer), input.c_str(), sizeof(tempBuffer) - 1);
        tempBuffer[sizeof(tempBuffer) - 1] = 0;
        if (ImGui::InputText(label.c_str(), tempBuffer, bufferSize)) input = tempBuffer;
        ImGui::SetWindowFontScale(1);
    }
};

#endif