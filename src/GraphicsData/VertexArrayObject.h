#ifndef _VERTEXARRAYOBJECT_H_
#define _VERTEXARRAYOBJECT_H_

#include "GL\glew.h"
#include "Config.h"

typedef struct {
	GLuint			m_index;
	GLint			m_size;
	GLenum			m_type;
	GLsizei			m_stride;
	const GLvoid *	m_offsetPointer;
}Attribute;

class VertexArrayObject
{
private:
	GLuint	m_handle;
	GLuint	m_numAttributes;
public:
	VertexArrayObject();
	~VertexArrayObject();

	void bind();
	void setAttribute(Attribute attribute);
	void enableAttribute(int index);
	void enableAllAttributes();
	GLuint getNumAttributes();
	void unbind();
};

#endif