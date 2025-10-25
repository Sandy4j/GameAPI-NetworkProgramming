#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>
#include <imgui/imgui.h>
#include <glm/glm.hpp>

struct TextBox
{
public:
    std::string label;
    std::string input;
    glm::vec2 position;
    float size;

public:
    void Draw()
    {
        ImGui::SetCursorPos(ImVec2(position.x, position.y));
        ImGui::SetWindowFontScale(size);

        const size_t bufferSize = 256;
        char tempBuffer[bufferSize];
        strncpy_s(tempBuffer, sizeof(tempBuffer), input.c_str(), sizeof(tempBuffer) - 1);
        tempBuffer[sizeof(tempBuffer) - 1] = 0;
        if (ImGui::InputText(label.c_str(), tempBuffer, bufferSize)) input = tempBuffer;
        ImGui::SetWindowFontScale(1);
    }
};

#endif