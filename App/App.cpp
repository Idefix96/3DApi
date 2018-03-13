#include <GL\glew.h>
#include <SFML\Window.hpp>
#include <SFML/OpenGL.hpp>
#include "3DMesh\3DMesh.h"
#include "Shader\Shader.h"
#include "Scene\Camera\Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <math.h>


int main()
{
	// create the window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	// activate the window
	window.setActive(true);
	glewInit();
	PositionData pd;
	pd.push_back(Position(0,0,0));
	pd.push_back(Position(1, 1, 0));
	pd.push_back(Position(-1, 1, 0));
	NormalData nd;
	nd.push_back(Position(2, 2, 0));
	nd.push_back(Position(-2, -2, 0));
	nd.push_back(Position(3, 3, 0));
	Mesh3D mesh;
	mesh.setPositionData(pd);
	mesh.setNormalData(nd);
	Shader shader;
	shader.loadProgram("simple");
	Camera camera;
	
	// run the main loop
	bool running = true;
	while (running)
	{
		static float angle = 0.0;
		camera.move(Direction(0,0,std::sin(angle)));
		angle += 0.1;
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
		glUseProgram(shader.getShaderID());
		glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "gPersp"), 1, GL_FALSE, glm::value_ptr(camera.getPerspectiveMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "gWorldToCamera"), 1, GL_FALSE, glm::value_ptr(camera.getWorldToCameraMatrix()));
		mesh.Draw();
		
		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}