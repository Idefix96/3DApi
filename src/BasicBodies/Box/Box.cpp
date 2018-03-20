#include "Box.h"

Box::Box()
{
	PositionData pd;
	NormalData nd;
	IndexData id;
	this->m_width = 1.0f;
	this->m_height = 1.0f;
	this->m_depth = 1.0f;
	float halfWidth = this->m_width / 2.0f;
	float halfHeight = this->m_height / 2.0f;
	float halfDepth = this->m_depth / 2.0f;

	//bottom
	pd.push_back(Position(-halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, -halfHeight, -halfDepth));
	nd.push_back(Direction(0, -1, 0));
	nd.push_back(Direction(0, -1, 0));
	nd.push_back(Direction(0, -1, 0));
	nd.push_back(Direction(0, -1, 0));
	id.push_back(0);
	id.push_back(1);
	id.push_back(2);
	id.push_back(3);
	id.push_back(2);
	id.push_back(0);
	//left
	
	pd.push_back(Position(-halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, -halfDepth));
	nd.push_back(Direction(-1, 0, 0));
	nd.push_back(Direction(-1, 0, 0));
	nd.push_back(Direction(-1, 0, 0));
	nd.push_back(Direction(-1, 0, 0));
	id.push_back(4);
	id.push_back(5);
	id.push_back(6);
	id.push_back(7);
	id.push_back(6);
	id.push_back(4);
	
	//right
	pd.push_back(Position(halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, -halfDepth));
	nd.push_back(Direction(1, 0, 0));
	nd.push_back(Direction(1, 0, 0));
	nd.push_back(Direction(1, 0, 0));
	nd.push_back(Direction(1, 0, 0));
	id.push_back(8);
	id.push_back(9);
	id.push_back(10);
	id.push_back(11);
	id.push_back(10);
	id.push_back(8);
	
	//front
	pd.push_back(Position(halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, halfDepth));
	nd.push_back(Direction(0, 0, 1));
	nd.push_back(Direction(0, 0, 1));
	nd.push_back(Direction(0, 0, 1));
	nd.push_back(Direction(0, 0, 1));
	id.push_back(12);
	id.push_back(13);
	id.push_back(14);
	id.push_back(15);
	id.push_back(14);
	id.push_back(13);
	
	//back
	pd.push_back(Position(halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, -halfDepth));
	nd.push_back(Direction(0, 0, -1));
	nd.push_back(Direction(0, 0, -1));
	nd.push_back(Direction(0, 0, -1));
	nd.push_back(Direction(0, 0, -1));
	id.push_back(16);
	id.push_back(17);
	id.push_back(18);
	id.push_back(19);
	id.push_back(18);
	id.push_back(17);
	
	//top
	pd.push_back(Position(-halfWidth, halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, -halfDepth));
	nd.push_back(Direction(0, 1, 0));
	nd.push_back(Direction(0, 1, 0));
	nd.push_back(Direction(0, 1, 0));
	nd.push_back(Direction(0, 1, 0));
	id.push_back(20);
	id.push_back(21);
	id.push_back(22);
	id.push_back(23);
	id.push_back(22);
	id.push_back(20);
	
	this->m_material.setHasTexture(false);
	
	this->setPositionData(pd);
	this->setNormalData(nd);
	this->setIndexData(id);

	//TODO: set index data
}

Box::Box(float width, float height, float depth)
{
	PositionData pd;
	NormalData nd;
	this->m_width = width;
	this->m_height = height;
	this->m_depth = depth;
	float halfWidth = this->m_width / 2.0f;
	float halfHeight = this->m_height / 2.0f;
	float halfDepth = this->m_depth / 2.0f;

	//bottom
	pd.push_back(Position(-halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, -halfHeight, -halfDepth));
	nd.push_back(Direction(0, -1, 0));
	nd.push_back(Direction(0, -1, 0));
	nd.push_back(Direction(0, -1, 0));
	nd.push_back(Direction(0, -1, 0));
	/*
	//left
	pd.push_back(Position(-halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, -halfDepth));
	nd.push_back(Direction(-1, 0, 0));
	nd.push_back(Direction(-1, 0, 0));
	nd.push_back(Direction(-1, 0, 0));
	nd.push_back(Direction(-1, 0, 0));
	//right
	pd.push_back(Position(halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, -halfDepth));
	nd.push_back(Direction(1, 0, 0));
	nd.push_back(Direction(1, 0, 0));
	nd.push_back(Direction(1, 0, 0));
	nd.push_back(Direction(1, 0, 0));
	//front
	pd.push_back(Position(halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, halfDepth));
	nd.push_back(Direction(0, 0, 1));
	nd.push_back(Direction(0, 0, 1));
	nd.push_back(Direction(0, 0, 1));
	nd.push_back(Direction(0, 0, 1));
	//back
	pd.push_back(Position(halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, -halfDepth));
	nd.push_back(Direction(0, 0, -1));
	nd.push_back(Direction(0, 0, -1));
	nd.push_back(Direction(0, 0, -1));
	nd.push_back(Direction(0, 0, -1));
	//top
	pd.push_back(Position(-halfWidth, halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, -halfDepth));
	nd.push_back(Direction(0, 1, 0));
	nd.push_back(Direction(0, 1, 0));
	nd.push_back(Direction(0, 1, 0));
	nd.push_back(Direction(0, 1, 0));
	*/
	this->setPositionData(pd);
	this->setNormalData(nd);

	//TODO: set index data
}