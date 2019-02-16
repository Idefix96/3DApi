#pragma once

#include "3DMesh\3DMesh.h"
#include "Shader\Shader.h"
#include "Scene\Camera\Camera.h"
#include "Scene\Light\AmbientLight.h"
#include "Scene\Light\DirectionalLight.h"

class Scene
{

private:
	std::vector<Shader*> m_shader;
	std::vector<std::pair<Mesh3D*, GLuint>> m_meshes;
	Camera*	m_camera;
	AmbientLight* m_ambientLight;
	DirectionalLight* m_directionalLight;

public:
	Scene();

	void addShader(Shader* shader)
	{
		m_shader.push_back(shader);
	}

	void addMesh(Mesh3D* mesh, GLuint shaderId)
	{
		m_meshes.push_back(std::make_pair(mesh, shaderId));
	}

	void addAmbientLight(AmbientLight* light)
	{
		this->m_ambientLight = light;
	}

	void addDirectionalLight(DirectionalLight* light)
	{
		this->m_directionalLight = light;
	}

	void addCamera(Camera* camera)
	{
		this->m_camera = camera;
	}

	void draw()
	{
		m_camera->doAction();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto&& shader : m_shader)
		{
			glUseProgram(shader->getShaderID());
			glUniformMatrix4fv(glGetUniformLocation(shader->getShaderID(), "gPersp"), 1, GL_FALSE, glm::value_ptr(m_camera->getPerspectiveMatrix()));
			glUniformMatrix4fv(glGetUniformLocation(shader->getShaderID(), "gWorldToCamera"), 1, GL_FALSE, glm::value_ptr(m_camera->getWorldToCameraMatrix()));
			glUniform3fv(glGetUniformLocation(shader->getShaderID(), "cameraPosition"), 1, glm::value_ptr(m_camera->getPosition()));
			glUniform4fv(glGetUniformLocation(shader->getShaderID(), "AmbientColor"), 1, glm::value_ptr(m_ambientLight->getColor()));
			glUniform1f(glGetUniformLocation(shader->getShaderID(), "AmbientIntensity"), m_ambientLight->getIntensity());
			glUniform4fv(glGetUniformLocation(shader->getShaderID(), "DirectionalColor"), 1, glm::value_ptr(m_directionalLight->getColor()));
			glUniform1f(glGetUniformLocation(shader->getShaderID(), "DirectionalIntensity"), m_directionalLight->getIntensity());
			glUniform3fv(glGetUniformLocation(shader->getShaderID(), "DirectionalDirection"), 1, glm::value_ptr(m_directionalLight->getDirection()));
		}
		for (auto&& mesh : m_meshes)
		{		
			mesh.first->Draw(mesh.second);
		}
		glBindVertexArray(NULL);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glUseProgram(NULL);
	}

	~Scene();
};

