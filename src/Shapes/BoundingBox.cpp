#include "BoundingBox.h"


BoundingBox::BoundingBox(float width, float height, float depth) :
	m_width(width),
	m_height(height),
	m_depth(depth)
{
	PositionData pd;
	IndexData id;

	float halfWidth = this->m_width / 2.0f;
	float halfHeight = this->m_height / 2.0f;
	float halfDepth = this->m_depth / 2.0f;
	//bottom
	pd.push_back(Position(-halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, -halfHeight, -halfDepth));
	id.push_back(0);
	id.push_back(1);
	id.push_back(1);
	id.push_back(2);
	id.push_back(2);
	id.push_back(3);
	id.push_back(3);
	id.push_back(0);
	//top
	pd.push_back(Position(-halfWidth, halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, -halfDepth));
	id.push_back(4);
	id.push_back(5);
	id.push_back(5);
	id.push_back(6);
	id.push_back(6);
	id.push_back(7);
	id.push_back(7);
	id.push_back(4);
	//top to bottm
	id.push_back(4);
	id.push_back(0);
	id.push_back(5);
	id.push_back(1);
	id.push_back(6);
	id.push_back(2);
	id.push_back(7);
	id.push_back(3);

	this->setPositionData(pd);
	this->setIndexData(id);
	
}

void BoundingBox::Draw(GLuint shader)
{
	this->m_vdm.bindVAO();
	glUniform1i(glGetUniformLocation(shader, "hasTexture"), this->m_material.hasTexture());
	glUniform1i(glGetUniformLocation(shader, "hasNormalMap"), this->m_material.hasTexture());
	glUniform1f(glGetUniformLocation(shader, "shininess"), this->m_material.getShininess());
	glUniform1f(glGetUniformLocation(shader, "shininessStrength"), this->m_material.getShininessStrength());
	glDrawElements(GL_LINES, this->m_indexData.size(), GL_UNSIGNED_INT, 0);
}