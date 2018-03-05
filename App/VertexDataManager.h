#pragma once

#include "Buffer.h"
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
	const GLvoid *m_dataPointer;
	Attribute m_position;
public:
	VertexDataManager();
	~VertexDataManager();
	void setVertexData(const GLvoid *data);
	void enablePosition();
	void enableUV();
	void enableNormals();
	void enableTangents();
	void enableBitangents();
	void bindVAO();
};

