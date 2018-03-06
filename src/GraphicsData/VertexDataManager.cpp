#include "VertexDataManager.h"
#include <iostream>
VertexDataManager::VertexDataManager()
{
	m_positionDataPointer = NULL;
	m_normalDataPointer = NULL;
	m_VBO.setTarget(GL_ARRAY_BUFFER);
	m_IBO.setTarget(GL_ELEMENT_ARRAY_BUFFER);

	m_position.m_index = 0;
	m_position.m_size = 3;
	m_position.m_type = GL_FLOAT;
	m_position.m_stride = sizeof(Position);
	m_position.m_offsetPointer = (void*)0;
}


VertexDataManager::~VertexDataManager()
{
}

void VertexDataManager::setVertexPositionData(const GLvoid *data)
{	
	this->m_positionDataPointer = data;
}

void VertexDataManager::setVertexNormalData(const GLvoid *data)
{
	this->m_normalDataPointer = data;
}

void VertexDataManager::enablePosition()
{
	m_VAO.bind();
	m_VBO.bind();

	glBufferData(GL_ARRAY_BUFFER, 3*sizeof(m_positionDataPointer), this->m_positionDataPointer, GL_STATIC_DRAW);
	m_VAO.setAttribute(m_position);
	m_VAO.enableAttribute(m_position.m_index);
	
}

void VertexDataManager::enableUV()
{

}

void VertexDataManager::enableNormals()
{
	m_VAO.bind();
	m_VBO.bind();
	m_normal.m_index = m_VAO.getNumAttributes();
	m_normal.m_size = 3;
	m_normal.m_type = GL_FLOAT;
	m_normal.m_stride = sizeof(Normal);
	m_normal.m_offsetPointer = (void*)0;
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_position), sizeof(m_normal), m_normalDataPointer);
	m_VAO.setAttribute(m_normal);
	m_VAO.enableAttribute(m_normal.m_index);
}

void VertexDataManager::enableTangents()
{

}

void VertexDataManager::enableBitangents()
{

}

void VertexDataManager::bindVAO()
{
	this->m_VAO.bind();
}

