#include "stdafx.h"
#include "Buffer.h"


Buffer::Buffer()
{
	glGenBuffers(1, &(this->m_handle));
}


Buffer::~Buffer()
{
	glDeleteBuffers(1, &this->m_handle);
}

void Buffer::bind()
{
	glBindBuffer(this->m_target, this->m_handle);
}

void Buffer::setTarget(GLenum target)
{
	this->m_target = target;
}

GLenum Buffer::getTarget()
{
	return this->m_target;
}
