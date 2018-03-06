#include "VertexArrayObject.h"


VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &this->m_handle);

	m_numAttributes = 0;
}


VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &this->m_handle);
}

void VertexArrayObject::bind()
{
	glBindVertexArray(this->m_handle);
}

void VertexArrayObject::unbind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::setAttribute(Attribute attribute)
{
	glVertexAttribPointer(attribute.m_index, attribute.m_size, attribute.m_type, GL_FALSE, attribute.m_stride, attribute.m_offsetPointer);
	m_numAttributes += 1;
}

void VertexArrayObject::enableAttribute(int index)
{
	glEnableVertexAttribArray(index);
}

void VertexArrayObject::enableAllAttributes()
{
	for (GLuint i = 0; i < this->m_numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

GLuint VertexArrayObject::getNumAttributes()
{
	return this->m_numAttributes;
}
