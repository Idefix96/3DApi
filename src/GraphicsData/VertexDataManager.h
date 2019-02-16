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
	std::vector<AlphaColor> m_colorData;
	std::vector<VertexWeights> m_vertexWeightData;
	std::vector<BoneId> m_boneIdData;
	Attribute m_position;
	Attribute m_uvCoordinates;
	Attribute m_normal;
	Attribute m_tangent;
	Attribute m_bitangent;
	Attribute m_color;
	Attribute m_vertexWeight;
	Attribute m_boneId;
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
	void setVertexColorData(ColorData data);
	void setVertexWeightData(VertexWeightData data);
	void setVertexBoneIdData(BoneIdData data);
	void enablePosition();
	void enableUV();
	void enableNormals();
	void enableTangents();
	void enableBitangents();
	void enableVertexWeights();
	void enableBoneIds();
	void bindVAO();
};

