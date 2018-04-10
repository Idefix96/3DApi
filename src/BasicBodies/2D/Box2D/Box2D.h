#ifndef _BOX2D_H_
#define _BOX2D_H_

#include "3DMesh\3DMesh.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "Text\Text.h"

class Box2D : public Mesh3D
{
private:
	float m_width;
	float m_height;
	Position2D m_position;
	AlphaColor m_defaultColor;
	AlphaColor m_mouseOverColor;
	AlphaColor m_clickedColor;
	Text m_text;
public:
	Box2D(float width, float height);

	void setColor(AlphaColor color);
	bool isMouseOver(float x, float y, float windowWidth, float WindowHeight, sf::RenderWindow *window);
	bool isClicked(float x, float y, float windowWidth, float windowHeight, sf::RenderWindow *window);
	void setMouseOverColor(AlphaColor color);
	void setClickedColor(AlphaColor color);
	void display(GLuint shader, GLuint textShader, float windowWidth, float windowHeight);
};

#endif