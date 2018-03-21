#ifndef _3DMESH_H_
#define _3DMESH_H_

#include "types.h"
#include "GraphicsData\VertexDataManager.h"
#include "Config.h"
#include "Material\Material.h"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/transform.hpp"


class Mesh3D
{
protected:
	VertexDataManager	m_vdm;
	PositionData		m_positionData;
	NormalData			m_normalData;
	IndexData			m_indexData;
	UVData				m_UvData;
	TangentData			m_tangentData;
	BitangentData		m_bitangentData;
	Material			m_material;

	Position			m_currentPosition;
	Rotation			m_currentRotation;
	RotationMatrix		m_rotationMatrix;
	TranslationMatrix	m_translationMatrix;
	ScalingMatrix		m_scalingMatrix;

public:
	Mesh3D();
	~Mesh3D();

	void setPositionData(PositionData data);
	void setNormalData(NormalData data);
	void setIndexData(IndexData data);
	void setUVData(UVData data);
	void setTangentData(TangentData data);
	void setBitangentData(BitangentData data);
	void setMaterial(Material material);
	void Draw(GLuint shader);
	void rotate(Direction angle);
	void translate(Position position);
	void scale(Scale scale);
};

#endif
