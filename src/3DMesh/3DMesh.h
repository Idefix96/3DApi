#ifndef _3DMESH_H_
#define _3DMESH_H_

#include "types.h"
#include "GraphicsData\VertexDataManager.h"
#include "Config.h"
#include "Material\Material.h"

class Mesh3D
{
private:
	VertexDataManager	m_vdm;
	PositionData		m_positionData;
	NormalData			m_normalData;
	IndexData			m_indexData;
	UVData				m_UvData;
	TangentData			m_tangentData;
	BitangentData		m_bitangentData;
	Material			m_material;

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
};

#endif
