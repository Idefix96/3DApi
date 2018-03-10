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
	std::vector<Position> m_positionData;
	std::vector<Normal> m_normalData;
	Attribute m_position;
	Attribute m_uvCoordinates;
	Attribute m_normal;
public:
	VertexDataManager();
	~VertexDataManager();
	void setVertexPositionData(std::vector<Position> data);
	void setVertexNormalData(std::vector<Normal> data);
	void enablePosition();
	void enableUV();
	void enableNormals();
	void enableTangents();
	void enableBitangents();
	void bindVAO();
};

