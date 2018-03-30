#include "Button.h"
#include <iostream>

Button::Button()
{
//	this->m_defaultColor = AlphaColor(0.3f, 0.3f, 0.3f, 0.75f);
}

Button::Button(std::string text, float width, float height, sf::RenderWindow* window)
{
	this->m_defaultColor = AlphaColor(0.3f, 0.3f, 0.3f, 0.75f);
}

Button::~Button()
{

}

void Button::setColor(AlphaColor color)
{

	
}

bool Button::mouseOverCallback(float x, float y)
{
	return true;
}

void Button::setText(std::string text)
{

}




void Button::draw(sf::RenderStates state)
{
	
}
