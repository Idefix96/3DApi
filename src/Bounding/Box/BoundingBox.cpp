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

	//front
	pd.push_back(Position(halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, halfDepth));
	id.push_back(0);
	id.push_back(1);
	id.push_back(1);
	id.push_back(2);
	id.push_back(2);
	id.push_back(3);
	id.push_back(3);
	id.push_back(0);

	//back
	pd.push_back(Position(halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, -halfHeight, -halfDepth));
	pd.push_back(Position(-halfWidth, halfHeight, -halfDepth));
	pd.push_back(Position(halfWidth, halfHeight, -halfDepth));
	id.push_back(4);
	id.push_back(5);
	id.push_back(5);
	id.push_back(6);
	id.push_back(6);
	id.push_back(7);
	id.push_back(7);
	id.push_back(4);

	id.push_back(0);
	id.push_back(4);
	id.push_back(1);
	id.push_back(5);
	id.push_back(2);
	id.push_back(6);
	id.push_back(3);
	id.push_back(7);

	this->setPositionData(pd);
	this->setIndexData(id);

	this->m_material.setDiffuseAlphaColor(AlphaColor(1.f, 0.f, 0.f, 1.f));
}

void BoundingBox::Draw(GLuint shader)
{
	glUseProgram(shader);
	this->m_vdm.bindVAO();
	glUniform4fv(glGetUniformLocation(shader, "materialColor"), 1, glm::value_ptr(this->m_material.getDiffuseAlphaColor()));
	glUniformMatrix4fv(glGetUniformLocation(shader, "gScaling"), 1, GL_FALSE, glm::value_ptr(this->m_scalingMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader, "gRotation"), 1, GL_FALSE, glm::value_ptr(this->m_rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader, "gTranslation"), 1, GL_FALSE, glm::value_ptr(this->m_translationMatrix));
	glDrawElements(GL_LINES, this->m_indexData.size(), GL_UNSIGNED_INT, 0);
}