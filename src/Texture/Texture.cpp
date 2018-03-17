#include "Texture.h"
#include <iostream>
void Texture::loadTexture(std::string file)
{
	this->m_handle = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
}

GLuint Texture::getTexture()
{
	return this->m_handle;
}