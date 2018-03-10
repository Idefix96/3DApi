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
	this->m_vdm.enablePosition();
}

void Mesh3D::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, this->m_positionData.size());
}