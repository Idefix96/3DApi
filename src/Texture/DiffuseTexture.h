#ifndef _DIFFUSETEXTURE_H_
#define _DIFFUSETEXTURE_H_

#include "GL\glew.h"
#include "Config.h"
#include <string>
#include "SOIL.h"

class DiffuseTexture
{
private:
	GLuint m_handle;

public:
	void loadTexture(std::string file);
	GLuint getTexture();
};

#endif
