#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <imgui/imgui.h>
#include <glad/glad.h>
#include "UiTransform.h"

struct Image
{
public:
	UiTransform* transform;
	GLuint textureID = 0;
	ImVec2 baseSize = ImVec2(100.0f, 100.0f);

	ImVec2 uv0 = ImVec2(0, 0);
	ImVec2 uv1 = ImVec2(1, 1);
	ImVec4 tintColor = ImVec4(1, 1, 1, 1);

public:
	void Draw()
	{
		if (!transform || !transform->b_is_active || textureID == 0) return;

		ImVec2 finalSize = ImVec2(
			baseSize.x * transform->scale.x,
			baseSize.y * transform->scale.y
		);

		ImGui::SetCursorPos(ImVec2(transform->position.x, transform->position.y));
		ImTextureID texID = (ImTextureID)textureID;
		ImGui::Image(texID, finalSize, uv0, uv1);
		ImGui::SetWindowFontScale(5);
		ImGui::Text("Test Gambar di atas");
		ImGui::SetWindowFontScale(1);
		//ImGui::Image(texID, finalSize, uv0, uv1, tintColor);
	}
};

#endif
