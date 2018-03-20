#include "BoundingBox.h"

BoundingBox::BoundingBox()
{

}

void BoundingBox::Draw(GLuint shader)
{
	glDrawElements(GL_LINES, this->m_indexData.size(), GL_UNSIGNED_INT, 0);
}