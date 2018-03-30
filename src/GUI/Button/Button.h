#include "Text/Text.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "types.h"


#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button
{

	private:
		AlphaColor	m_mouseOverColor;
		AlphaColor	m_defaultColor;;
		float		m_width;
		float		m_height;
		bool		m_active;
		sf::Font	m_font;
		sf::Text	m_text;
		sf::RenderWindow* m_window;
		sf::RectangleShape m_rect;
		sf::Texture	m_texture;
		sf::RenderStates m_state;
	public:
		Button(void);
		~Button(void);
		Button(std::string text, float width, float height, sf::RenderWindow* window);

		void setText(std::string text);
		void setColor(AlphaColor color);
		bool mouseOverCallback(float x, float y);
		void draw(sf::RenderStates state);
};

#endif