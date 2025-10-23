#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;
out vec3 currentPos;

uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;

void main()
{
   currentPos = vec3(modelMatrix * vec4(aPos, 1.0f));
   gl_Position = cameraMatrix * vec4(currentPos, 1.0f);

   color = aColor;
   texCoord = aTex;
}