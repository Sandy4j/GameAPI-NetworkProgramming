#include "ShaderProgram.h"

#include <glm\gtc\type_ptr.hpp>

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

void ShaderProgram::SetMatrix4Uniform(const char* uniform, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, uniform), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::SetVector4Uniform(const char* uniform, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(ID, uniform), value.x, value.y, value.z, value.w);
}

void ShaderProgram::SetVector3Uniform(const char* uniform, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(ID, uniform), value.x, value.y, value.z);
}

void ShaderProgram::SetFloatUniform(const char* uniform, float value)
{
	glUniform1f(glGetUniformLocation(ID, uniform), value);
}

void ShaderProgram::Load(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::Activate()
{
	glUseProgram(ID);
}

GLuint ShaderProgram::GetID()
{
	return ID;
}

void ShaderProgram::Delete()
{
	glDeleteProgram(ID);
}