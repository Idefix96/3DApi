#ifndef _Texture_H_
#define _Texture_H_

#include "GL\glew.h"
#include "Config.h"
#include <string>
#include "SOIL.h"

class Texture
{
private:
	GLuint m_handle;

public:
	void loadTexture(std::string file);
	GLuint getTexture();
};

#endif
