#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "GL\glew.h"

class Buffer
{
	private:
		GLenum	m_target;
		GLuint	m_handle;
	
	public:
		Buffer();
		~Buffer();

		GLenum	getTarget();
		void	bind();
		void	setTarget(GLenum target);
};	

#endif

