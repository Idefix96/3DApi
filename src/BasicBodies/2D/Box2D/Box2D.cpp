#include "stdafx.h"
#include "Box2D.h"
#include "GL\glew.h"

Box2D::Box2D(float width, float height) :
	m_width(width),
	m_height(height)
{
	PositionData pd;
	IndexData id;

	float halfWidth = this->m_width / 2.0f;
	float halfHeight = this->m_height / 2.0f;

	this->m_position = Position2D(0.f, 0.f);

	pd.push_back(Position(halfWidth, -halfHeight, 0));
	pd.push_back(Position(-halfWidth, -halfHeight, 0));
	pd.push_back(Position(halfWidth, halfHeight, 0));
	pd.push_back(Position(-halfWidth, halfHeight, 0));
	
	id.push_back(0);
	id.push_back(2);
	id.push_back(1);
	id.push_back(3);
	id.push_back(1);
	id.push_back(2);

	this->setPositionData(pd);
	this->setIndexData(id);

	this->m_defaultColor = AlphaColor(0.25, 0.25, 0.25, 0.6);
	this->m_mouseOverColor = this->m_defaultColor + AlphaColor(-0.1, -0.1, -0.1, 0.3);
	this->m_clickedColor = this->m_defaultColor + AlphaColor(0.7, 0.7, 0.7, 0.3);
}

void Box2D::setColor(AlphaColor color)
{
	this->m_material.setDiffuseAlphaColor(color);
	this->m_defaultColor = color;
}

void Box2D::setMouseOverColor(AlphaColor color)
{
	this->m_mouseOverColor = color;
}

void Box2D::setClickedColor(AlphaColor color)
{
	this->m_clickedColor = color;
}

bool Box2D::isMouseOver(float x, float y, float windowWidth, float windowHeight, sf::RenderWindow *window)
{
	
	//transform from window to normalized coordinates
	float xNorm = 2*x / windowWidth - 1.f;
	float yNorm = -2*y / windowHeight + 1.f;
	//difference in y-direction after resize
	float diff = (float)(window->getSize().y - windowHeight);
	
	glm::vec4 position = this->m_translationMatrix * glm::vec4(this->m_position.x, this->m_position.y, 0.f, 1.f);
	
	float diffNorm = 2 * diff / windowHeight ;
	
	if ((abs(xNorm - position.x) <= this->m_width / 2.f)
		&& (abs(yNorm - position.y + diffNorm) <= this->m_height / 2.f))
	{
		this->m_material.setDiffuseAlphaColor(this->m_mouseOverColor);
		return true;
	}
	else
	{
		this->m_material.setDiffuseAlphaColor(this->m_defaultColor);
		return false;
	}
}

bool Box2D::isClicked(float x, float y, float windowWidth, float windowHeight, sf::RenderWindow *window)
{
	if ((this->isMouseOver(x, y, windowWidth, windowHeight, window)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		this->m_material.setDiffuseAlphaColor(this->m_clickedColor);
		return true;
	}
		return false;
}

void Box2D::display(GLuint shader, GLuint textShader, float windowWidth, float windowHeight)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glm::vec4 position = this->m_translationMatrix * glm::vec4(this->m_position.x, this->m_position.y, 0.f, 1.f);
	this->Draw(shader);
	
	this->m_text.display(textShader, "Test", position.x - this->m_width/2.f , position.y - this->m_height/2.f,  this->m_width,  this->m_height, windowWidth, windowHeight);
}