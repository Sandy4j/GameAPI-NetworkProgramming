#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

#include<glm/glm.hpp>

std::string get_file_contents(const char* filename);

class ShaderProgram
{
public:
	ShaderProgram() = default;
	~ShaderProgram() = default;

	void Load(const char* vertexFile, const char* fragmentFile);
	void Activate();
	GLuint GetID();
	void Delete();

	void SetMatrix4Uniform(const char* uniform, glm::mat4 value);
	void SetVector4Uniform(const char* uniform, glm::vec4 value);
	void SetVector3Uniform(const char* uniform, glm::vec3 value);
	void SetFloatUniform(const char* uniform, float value);

private:
	GLuint ID;

};

#endif