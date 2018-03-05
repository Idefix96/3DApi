#include <GL\glew.h>
#include <SFML\Window.hpp>
#include <SFML/OpenGL.hpp>
#include "Buffer.h"
#include "VertexDataManager.h"
#include "types.h"
int main()
{
	// create the window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	// activate the window
	window.setActive(true);
	glewInit();
	Vertex vertex;
	vertex.m_position = Position(0.5, 0, 0);
	Vertex vertex2;
	vertex2.m_position = Position(-0.5, 0, 0);

	VertexDataManager vdm;
	vdm.setVertexData(&vertex.m_position);
	vdm.enablePosition();

	VertexDataManager vdm2;
	vdm2.setVertexData(&vertex2.m_position);
	vdm2.enablePosition();
	
	// run the main loop
	bool running = true;
	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		vdm.bindVAO();
		glDrawArrays(GL_POINTS, 0, 1);
		vdm2.bindVAO();
		glDrawArrays(GL_POINTS, 0, 1);
		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}