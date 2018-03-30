#include "Box2D.h"

Box2D::Box2D(float width, float height) :
	m_width(width),
	m_height(height)
{
	PositionData pd;
	IndexData id;

	float halfWidth = this->m_width / 2.0f;
	float halfHeight = this->m_height / 2.0f;

	pd.push_back(Position(halfWidth, -halfHeight, 0));
	pd.push_back(Position(-halfWidth, -halfHeight, 0));
	pd.push_back(Position(halfWidth, halfHeight, 0));
	pd.push_back(Position(-halfWidth, halfHeight, 0));
	
	id.push_back(0);
	id.push_back(2);
	id.push_back(1);
	id.push_back(3);
	id.push_back(1);
	id.push_back(2);

	this->setPositionData(pd);
	this->setIndexData(id);
}

void Box2D::setColor(AlphaColor color)
{
	this->m_material.setDiffuseAlphaColor(color);
}