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
	std::vector<int> m_indexData;
	Attribute m_position;
	Attribute m_uvCoordinates;
	Attribute m_normal;
public:
	VertexDataManager();
	~VertexDataManager();
	void setVertexPositionData(PositionData data);
	void setVertexNormalData(NormalData data);
	void setVertexIndexData(IndexData data);
	void enablePosition();
	void enableUV();
	void enableNormals();
	void enableTangents();
	void enableBitangents();
	void bindVAO();
};

