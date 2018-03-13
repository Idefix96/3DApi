#include "3DMesh.h"

Mesh3D::Mesh3D()
{

}

Mesh3D::~Mesh3D()
{

}

void Mesh3D::setPositionData(PositionData data)
{
	this->m_positionData = data;
	this->m_vdm.setVertexPositionData(this->m_positionData);
}

void Mesh3D::setNormalData(NormalData data)
{
	this->m_normalData = data;
	this->m_vdm.setVertexNormalData(this->m_normalData);
}

void Mesh3D::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, this->m_positionData.size());
}