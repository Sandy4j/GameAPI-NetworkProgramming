#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <vector>

#include "Transform.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

struct Sprite
{
private:
	std::vector<Vertex> vertices = 
	{
		Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}
	};

	std::vector<GLuint> indices = 
	{
		0, 1, 2,
		1, 2, 3
	};

public:
	int layer = 0;

	Transform* transform;
	std::vector<std::string> location_textures;
	std::string location_fragment;
	std::string location_vertex;

	VAO* vao = new VAO();
	VBO* vbo = new VBO();
	EBO* ebo = new EBO();

	Texture* texture = new Texture();
	ShaderProgram* shader_program;


public:
	void ChangeColor(const glm::vec3& new_color)
	{
		for (auto& vert : vertices)
		{
			vert.color = new_color;
		}

		vao->Bind();
		vbo->Activate(vertices);
		ebo->Activate(indices);

		vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		vao->LinkAttrib(*vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

		vao->Unbind();
		vbo->Unbind();
		ebo->Unbind();
	}

	void ChangeTexture(const std::string newTex)
	{
		location_textures[0] = newTex;
		texture->Activate(location_textures[0].c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
	}

	void Init()
	{
		shader_program->Load(location_vertex.c_str(), location_fragment.c_str());

		vao->Bind();
		vbo->Activate(vertices);
		ebo->Activate(indices);

		vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		vao->LinkAttrib(*vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

		texture->Activate(location_textures[0].c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);

		vao->Unbind();
		vbo->Unbind();
		ebo->Unbind();
	}

	void Update()
	{
		shader_program->Activate();

		unsigned int numDiffuse = 0;
		unsigned int numSpecular = 0;

		std::string num;
		std::string type = texture->GetType();

		/*if (type == "diffuse")
			num = std::to_string(numDiffuse++);
		else if (type == "specular")
			num = std::to_string(numSpecular++);*/

		//texture->TextureUnit(*shader_program, (type + num).c_str(), 0);
		texture->TextureUnit(*shader_program, "diffuse0", 0);
		texture->Bind();

		shader_program->SetMatrix4Uniform("modelMatrix", transform->matrix_model);

		glDisable(GL_CULL_FACE);
		vao->Bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glEnable(GL_CULL_FACE);
	}

};

#endif
