#include "VertexDataManager.h"
#include <iostream>

VertexDataManager::VertexDataManager()
{

	this->m_VBO.setTarget(GL_ARRAY_BUFFER);
	this->m_IBO.setTarget(GL_ELEMENT_ARRAY_BUFFER);

	this->m_position.m_index = 0;
	this->m_position.m_size = 3;
	this->m_position.m_type = GL_FLOAT;
	this->m_position.m_stride = sizeof(Position);
	this->m_position.m_offsetPointer = (void*)0;
}


VertexDataManager::~VertexDataManager()
{
	
}

void VertexDataManager::setVertexPositionData(PositionData data)
{	
	m_VAO.bind();
	m_VBO.bind();
	this->m_positionData = data;
	glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*this->m_positionData.size(), &this->m_positionData[0], GL_STATIC_DRAW);
	m_VAO.setAttribute(this->m_position);
	this->m_VAO.setAttribute(this->m_position);
	m_VAO.enableAttribute(this->m_position.m_index);
}

void VertexDataManager::setVertexNormalData(NormalData data)
{
	m_VAO.bind();
	m_VBO.bind();
	this->m_normal.m_index = this->m_VAO.getNumAttributes();
	this->m_normal.m_size = 3;
	this->m_normal.m_type = GL_FLOAT;
	this->m_normal.m_stride = sizeof(Normal);
	this->m_normal.m_offsetPointer = (void*)0;
	this->m_normalData = data;
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Position)*this->m_positionData.size(), sizeof(Normal)*this->m_normalData.size(), &this->m_normalData[0]);
	m_VAO.setAttribute(this->m_normal);
	m_VAO.enableAttribute(this->m_normal.m_index);
}

void VertexDataManager::enablePosition()
{
	this->m_VAO.bind();
	this->m_VBO.bind();
	
	this->m_VAO.enableAttribute(this->m_position.m_index);
}

void VertexDataManager::enableUV()
{

}

void VertexDataManager::enableNormals()
{
	this->m_VAO.bind();
	this->m_VBO.bind();
	
	this->m_VAO.enableAttribute(this->m_normal.m_index);
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

