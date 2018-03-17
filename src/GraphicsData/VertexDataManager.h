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
	std::vector<UVCoordinates> m_uvData;
	std::vector<Tangent> m_tangentData;
	std::vector<Bitangent> m_bitangentData;
	Attribute m_position;
	Attribute m_uvCoordinates;
	Attribute m_normal;
	Attribute m_tangent;
	Attribute m_bitangent;
	int m_bufferActiveSize;

public:
	VertexDataManager();
	~VertexDataManager();
	void setVertexPositionData(PositionData data);
	void setVertexNormalData(NormalData data);
	void setVertexIndexData(IndexData data);
	void setVertexUVData(UVData data);
	void setVertexTangentData(TangentData data);
	void setVertexBitangentData(BitangentData data);
	void enablePosition();
	void enableUV();
	void enableNormals();
	void enableTangents();
	void enableBitangents();
	void bindVAO();
};

