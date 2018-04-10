#include "Text.h"


Text::Text()
{
	
	FT_Error error = FT_Init_FreeType(&m_library);

	if (FT_New_Face(m_library, FONT_PATH "Arial.ttf", 0, &m_face)) {
		fprintf(stderr, "Could not open font\n");
	}

	m_glyphSlot = m_face->glyph;

	glGenVertexArrays(1, &this->m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(this->m_vao);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindVertexArray(NULL);
}

void Text::display(GLuint shader, const char *text, float x, float y, float width, float height, float windowWidth, float windowHeight)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(shader);
	
	GLfloat black[4] = { 0, 0, 0, 1 };
	glUniform4fv(glGetUniformLocation(shader, "gColor"), 1, glm::value_ptr(AlphaColor(0,0,0,1)));
	
	const char *p;
	FT_Set_Pixel_Sizes(m_face, 0, 64);
	for (p = text; *p; p++) {

		if (FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
			continue;
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			m_glyphSlot->bitmap.width,
			m_glyphSlot->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			m_glyphSlot->bitmap.buffer
		);
		
		float c0 = windowHeight / (float)m_glyphSlot->bitmap.rows;
		
		float c1 = (float)m_glyphSlot->bitmap.width / (float)m_glyphSlot->bitmap.rows; 
		float c2 = (float)m_glyphSlot->bitmap_top / (float)m_glyphSlot->bitmap.rows;
		float c3 = (float)m_glyphSlot->bitmap_left / (float)m_glyphSlot->bitmap.rows;
		
		float height_new =   (float)m_glyphSlot->bitmap.rows * height/windowHeight;
		float width_new = c1*height_new; 
		float top_new = c2*height_new;
		float left_new = c3*height_new;
		
	/*	float x2 = x + m_glyphSlot->bitmap_left/windowWidth;
		float y2 = y + m_glyphSlot->bitmap_top / windowHeight;
		float w = m_glyphSlot->bitmap.width / windowWidth;
		float h =  m_glyphSlot->bitmap.rows / windowHeight; */
		float x2 = x + left_new;
		float y2 = y + top_new;
		float w =  width_new;
		float h = height_new;

		GLfloat box[4][4] = {
			//uv coordinates are y-flipped
			{ x2,     y2    , 0, 0 }, 
			{ x2 + w, y2    , 1, 0 },
			{ x2,     y2 - h, 0, 1 }, //<--- this is defined as the "text starting point"
			{ x2 + w, y2 - h, 1, 1 },
		};
		glBindVertexArray(this->m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		float c4 = (float)m_glyphSlot->advance.x /(64.f* (float)m_glyphSlot->bitmap.width);
		float c5 = (float)m_glyphSlot->advance.y /(64.f* (float)m_glyphSlot->bitmap.rows);
		x += c4 * width_new;
		y += c5 * height_new;

	}
	
	glDisable(GL_BLEND);
}