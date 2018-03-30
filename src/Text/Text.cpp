#include "Text.h"


Text::Text()
{
	
	FT_Error error = FT_Init_FreeType(&m_library);

	if (FT_New_Face(m_library, FONT_PATH "Arial.ttf", 0, &m_face)) {
		fprintf(stderr, "Could not open font\n");
	}
	FT_Set_Pixel_Sizes(m_face, 10, 12);
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

void Text::render(const char *text, float x, float y, float sx, float sy)
{
	const char *p;

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

		float x2 = x + m_glyphSlot->bitmap_left * sx;
		float y2 = -y - m_glyphSlot->bitmap_top * sy;
		float w = m_glyphSlot->bitmap.width * sx;
		float h = m_glyphSlot->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{ x2,     -y2    , 0, 0 },
			{ x2 + w, -y2    , 1, 0 },
			{ x2,     -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};
		glBindVertexArray(this->m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (m_glyphSlot->advance.x / 64) * sx;
		y += (m_glyphSlot->advance.y / 64) * sy;
	}
}

void Text::display(Shader shader)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(shader.getShaderID());
	
	GLfloat black[4] = { 0, 0, 0, 1 };
	glUniform4fv(glGetUniformLocation(shader.getShaderID(), "gColor"), 1, glm::value_ptr(AlphaColor(0,0,0,1)));

	float sx = 2.0 / 800;
	float sy = 2.0 / 600;



	FT_Set_Pixel_Sizes(m_face, 0, 48);
	render("The Small Texture Scaled Fox Jumps Over The Lazy Dog",
		0.0 , 0.0, sx * 0.5, sy * 0.5);
	
	
	glDisable(GL_BLEND);
}