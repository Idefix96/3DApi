#ifndef _3DMESH_H_
#define _3DMESH_H_

#include "types.h"
#include "GraphicsData\VertexDataManager.h"
#include "Config.h"

class Mesh3D
{
private:
	VertexDataManager	m_vdm;
	PositionData		m_positionData;
	NormalData			m_normalData;
	IndexData			m_indexData;

public:
	Mesh3D();
	~Mesh3D();

	void setPositionData(PositionData data);
	void setNormalData(NormalData data);
	void setIndexData(IndexData data);
	void Draw();
};

#endif
