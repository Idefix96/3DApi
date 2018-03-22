#include "Plane.h"

Plane::Plane(Position offset, Direction direction1, Direction direction2, float width, float length) :
	m_offset(offset),
	m_direction1(direction1),
	m_direction2(direction2),
	m_width(width),
	m_length(length)
{
	PositionData pd;
	NormalData nd;
	IndexData id;

	float halfWidth = this->m_width / 2.0f;
	float halfLength = this->m_length / 2.0f;
	
	pd.push_back(this->m_offset + halfWidth*m_direction1 + halfLength*m_direction2);
	pd.push_back(this->m_offset - halfWidth*m_direction1 + halfLength*m_direction2);
	pd.push_back(this->m_offset - halfWidth*m_direction1 - halfLength*m_direction2);
	pd.push_back(this->m_offset + halfWidth*m_direction1 - halfLength*m_direction2);
	nd.push_back(glm::cross(this->m_direction1, this->m_direction2));
	nd.push_back(glm::cross(this->m_direction1, this->m_direction2));
	nd.push_back(glm::cross(this->m_direction1, this->m_direction2));
	nd.push_back(glm::cross(this->m_direction1, this->m_direction2));
	id.push_back(0);
	id.push_back(1);
	id.push_back(2);
	id.push_back(3);
	id.push_back(2);
	id.push_back(0);

	this->m_material.setHasTexture(false);

	this->setPositionData(pd);
	this->setNormalData(nd);
	this->setIndexData(id);
}