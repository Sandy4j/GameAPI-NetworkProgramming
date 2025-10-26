#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "ShaderProgram.h"

class Texture
{
public:
	Texture() = default;
	~Texture() = default;
	
	void Activate(const char* image, const char* texType, GLenum slot, GLenum format, GLenum pixelType);
	void TextureUnit(ShaderProgram& shader, const char* uniform, GLuint unit);
	void Bind();
	const char* GetType();
	void Unbind();
	void Delete();

private:
	GLuint ID;
	const char* type;
	GLuint unit;
};

#endif