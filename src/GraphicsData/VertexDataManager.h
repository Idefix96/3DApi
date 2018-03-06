#pragma once

#include "Buffer/Buffer.h"
#include "VertexArrayObject.h"
#include "types.h"
#include <vector>

class VertexDataManager
{
private:
	VertexArrayObject m_VAO;
	Buffer	m_VBO;
	Buffer m_IBO;
	GLsizeiptr m_vertexDataSize;
	const GLvoid *m_positionDataPointer;
	const GLvoid *m_normalDataPointer;
	Attribute m_position;
	Attribute m_uvCoordinates;
	Attribute m_normal;
public:
	VertexDataManager();
	~VertexDataManager();
	void setVertexPositionData(const GLvoid *data);
	void setVertexNormalData(const GLvoid *data);
	void enablePosition();
	void enableUV();
	void enableNormals();
	void enableTangents();
	void enableBitangents();
	void bindVAO();
};

