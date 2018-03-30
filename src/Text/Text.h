#ifndef _TEXT_H_
#define _TEXT_H_

#include "GL\glew.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "Config.h"

#include "Shader\Shader.h"
#include <glm/gtc/type_ptr.hpp>

class Text
{

private:
	FT_Library m_library;
	FT_GlyphSlot m_glyphSlot;
	FT_Face m_face;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint tex;
public:
	Text();
	void render(const char *text, float x, float y, float sx, float sy);
	void display(Shader shader);
};

#endif