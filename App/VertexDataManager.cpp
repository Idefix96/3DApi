#include "stdafx.h"
#include "VertexDataManager.h"

VertexDataManager::VertexDataManager()
{
	m_dataPointer = NULL;
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

void VertexDataManager::setVertexData(const GLvoid *data)
{
	
	this->m_dataPointer = data;
	
}

void VertexDataManager::enablePosition()
{
	m_VAO.bind();
	m_VBO.bind();
	glBufferData(GL_ARRAY_BUFFER, 3 * GL_FLOAT, this->m_dataPointer, GL_STATIC_DRAW);
	m_VAO.setAttribute(m_position);
	m_VAO.enableAttribute(m_position.m_index);
	
}

void VertexDataManager::enableUV()
{

}

void VertexDataManager::enableNormals()
{

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

