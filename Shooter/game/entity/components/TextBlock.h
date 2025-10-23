#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include <string>
#include <imgui/imgui.h>
#include <glm/glm.hpp>

struct TextBlock
{
public:
    std::string label;
    glm::vec2 position;
    float size;

public:
    void Draw()
    {
        ImGui::SetCursorPos(ImVec2(position.x, position.y));
        ImGui::SetWindowFontScale(size);
        ImGui::Text(label.c_str());
        ImGui::SetWindowFontScale(1);
    }
};

#endif