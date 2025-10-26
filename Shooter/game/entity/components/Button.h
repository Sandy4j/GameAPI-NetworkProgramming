#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <imgui/imgui.h>

struct Button
{
public:
    std::string label;
    glm::vec2 position;
    glm::vec2 size;

public:
    void Draw()
    {
        ImGui::SetCursorPos(ImVec2(position.x, position.y));
        ImGui::Button(label.c_str(), ImVec2(size.x, size.y));
    }
};

#endif
