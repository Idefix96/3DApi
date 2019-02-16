#include "stdafx.h"
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
	this->m_VAO.bind();
	this->m_VBO.bind();
	this->m_positionData = data;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*this->m_positionData.size(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Position)*this->m_positionData.size(), &this->m_positionData[0]);
	m_bufferActiveSize = sizeof(Position)*this->m_positionData.size();
	m_VAO.setAttribute(this->m_position);
	this->m_VAO.setAttribute(this->m_position);
	this->m_VAO.enableAttribute(this->m_position.m_index);
}

void VertexDataManager::setVertexNormalData(NormalData data)
{
	this->m_VAO.bind();
	this->m_VBO.bind();
	this->m_normal.m_index = 1; // this->m_VAO.getNumAttributes();
	this->m_normal.m_size = 3;
	this->m_normal.m_type = GL_FLOAT;
	this->m_normal.m_stride = sizeof(Normal);
	this->m_normal.m_offsetPointer = (void*)(m_bufferActiveSize);
	this->m_normalData = data;
	glBufferSubData(GL_ARRAY_BUFFER, m_bufferActiveSize, sizeof(Normal)*this->m_normalData.size(), &this->m_normalData[0]);
	m_bufferActiveSize += sizeof(Normal)*this->m_normalData.size();
	m_VAO.setAttribute(this->m_normal);
	m_VAO.enableAttribute(this->m_normal.m_index);
}

void VertexDataManager::setVertexUVData(UVData data)
{
	this->m_VAO.bind();
	this->m_VBO.bind();

	this->m_uvCoordinates.m_index = 2;
	this->m_uvCoordinates.m_size = 2;
	this->m_uvCoordinates.m_type = GL_FLOAT;
	this->m_uvCoordinates.m_stride = sizeof(UVCoordinates);
	this->m_uvCoordinates.m_offsetPointer = (void*)(m_bufferActiveSize);
	this->m_uvData = data;
	glBufferSubData(GL_ARRAY_BUFFER, m_bufferActiveSize, sizeof(UVCoordinates)*this->m_uvData.size(), &this->m_uvData[0]);
	m_bufferActiveSize += sizeof(UVCoordinates)*this->m_uvData.size();
	m_VAO.setAttribute(this->m_uvCoordinates);
	m_VAO.enableAttribute(this->m_uvCoordinates.m_index);
}

void VertexDataManager::setVertexTangentData(TangentData data)
{
	this->m_VAO.bind();
	this->m_VBO.bind();

	this->m_tangent.m_index = 3;
	this->m_tangent.m_size = 3;
	this->m_tangent.m_type = GL_FLOAT;
	this->m_tangent.m_stride = sizeof(Tangent);
	this->m_tangent.m_offsetPointer = (void*)(m_bufferActiveSize);
	this->m_tangentData = data;
	
	glBufferSubData(GL_ARRAY_BUFFER, m_bufferActiveSize, sizeof(Tangent)*this->m_tangentData.size(), &this->m_tangentData[0]);
	m_bufferActiveSize += sizeof(Tangent)*this->m_tangentData.size();
	m_VAO.setAttribute(this->m_tangent);
	m_VAO.enableAttribute(this->m_tangent.m_index);
}

void VertexDataManager::setVertexBitangentData(BitangentData data)
{
	this->m_VAO.bind();
	this->m_VBO.bind();

	this->m_bitangent.m_index = 4;
	this->m_bitangent.m_size = 3;
	this->m_bitangent.m_type = GL_FLOAT;
	this->m_bitangent.m_stride = sizeof(Bitangent);
	this->m_bitangent.m_offsetPointer = (void*)(m_bufferActiveSize);
	this->m_bitangentData = data;
	
	glBufferSubData(GL_ARRAY_BUFFER, m_bufferActiveSize, sizeof(Bitangent)*this->m_bitangentData.size(), &this->m_bitangentData[0]);
	m_bufferActiveSize += sizeof(Bitangent)*this->m_bitangentData.size();
	m_VAO.setAttribute(this->m_bitangent);
	m_VAO.enableAttribute(this->m_bitangent.m_index);
}

void VertexDataManager::setVertexWeightData(VertexWeightData data)
{
	this->m_VAO.bind();
	this->m_VBO.bind();

	this->m_vertexWeight.m_index = 6;
	this->m_vertexWeight.m_size = 4;
	this->m_vertexWeight.m_type = GL_FLOAT;
	this->m_vertexWeight.m_stride = sizeof(VertexWeights);
	this->m_vertexWeight.m_offsetPointer = (void*)(m_bufferActiveSize);
	this->m_vertexWeightData = data;

	glBufferSubData(GL_ARRAY_BUFFER, m_bufferActiveSize, sizeof(VertexWeights)*this->m_vertexWeightData.size(), &this->m_vertexWeightData[0]);
	m_bufferActiveSize += sizeof(VertexWeights)*this->m_vertexWeightData.size();
	m_VAO.setAttribute(this->m_vertexWeight);
	m_VAO.enableAttribute(this->m_vertexWeight.m_index);
}

void VertexDataManager::setVertexBoneIdData(BoneIdData data)
{
	this->m_VAO.bind();
	this->m_VBO.bind();

	this->m_boneId.m_index = 7;
	this->m_boneId.m_size = 4;
	this->m_boneId.m_type = GL_FLOAT;
	this->m_boneId.m_stride = sizeof(BoneId);
	this->m_boneId.m_offsetPointer = (void*)(m_bufferActiveSize);
	this->m_boneIdData = data;

	glBufferSubData(GL_ARRAY_BUFFER, m_bufferActiveSize, sizeof(BoneId)*this->m_boneIdData.size(), &this->m_boneIdData[0]);
	m_bufferActiveSize += sizeof(BoneId)*this->m_boneIdData.size();
	m_VAO.setAttribute(this->m_boneId);
	m_VAO.enableAttribute(this->m_boneId.m_index);
}

void VertexDataManager::setVertexColorData(ColorData data)
{
	this->m_VAO.bind();
	this->m_VBO.bind();

	this->m_color.m_index = 5;
	this->m_color.m_size = 4;
	this->m_color.m_type = GL_FLOAT;
	this->m_color.m_stride = sizeof(AlphaColor);
	this->m_color.m_offsetPointer = (void*)(m_bufferActiveSize);
	this->m_colorData = data;

	glBufferSubData(GL_ARRAY_BUFFER, m_bufferActiveSize, sizeof(AlphaColor)*this->m_colorData.size(), &this->m_colorData[0]);
	m_bufferActiveSize += sizeof(AlphaColor)*this->m_colorData.size();
	m_VAO.setAttribute(this->m_color);
	m_VAO.enableAttribute(this->m_color.m_index);
}

void VertexDataManager::setVertexIndexData(IndexData data)
{
	this->m_VAO.bind();
	this->m_IBO.bind();
	this->m_indexData = data;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*this->m_indexData.size(), &this->m_indexData[0], GL_STATIC_DRAW);
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

void VertexDataManager::enableVertexWeights()
{

}
void VertexDataManager::enableBoneIds()
{

}

void VertexDataManager::bindVAO()
{
	this->m_VAO.bind();
}

