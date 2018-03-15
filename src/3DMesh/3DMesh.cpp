#include "3DMesh.h"
#include <iostream>

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

void Mesh3D::setIndexData(IndexData data)
{
	this->m_indexData = data;
	this->m_vdm.setVertexIndexData(this->m_indexData);
}

void Mesh3D::Draw()
{
	this->m_vdm.bindVAO();
	if (this->m_indexData.size() > 0)
		glDrawElements(GL_TRIANGLES, this->m_indexData.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, this->m_positionData.size());
}