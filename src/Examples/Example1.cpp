#include <GL\glew.h>

#include <SFML\Window.hpp>
#include <SFML/OpenGL.hpp>
#include "3DMesh\3DMesh.h"
#include "Shader\Shader.h"
#include "Scene\Camera\Camera.h"
#include "3DMesh\ModelLoader.h"
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include "Scene\Light\AmbientLight.h"
#include "Scene\Light\DirectionalLight.h"
#include "BasicBodies\Box\Box.h"
#include "Shapes\BoundingBox.h"
#include "Physics\Physics.h"
#include "BasicBodies\Plane\Plane.h"
#include "GUI\Button\Button.h"
#include "Text\Text.h"

int main()
{	

	// create the window
	sf::ContextSettings Settings;
	Settings.depthBits = 24;
	Settings.stencilBits = 8;  // Request a 8 bits stencil buffer
	Settings.antialiasingLevel = 2;
	Settings.majorVersion = 4;
	Settings.minorVersion = 4;
	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, Settings);
	window.setVerticalSyncEnabled(true);
	Physics physics;
	// activate the window
	window.setActive(true);
	glewInit();

	Shader shader;
	shader.loadProgram("simple");
	Shader shader2D;
	shader2D.loadProgram("2D/Text");
	Camera camera;
	AmbientLight light;
	light.setIntensity(0.3);
	light.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	DirectionalLight dirLight;
	dirLight.setIntensity(1.0);
	dirLight.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	dirLight.setDirection(Direction(0.0, -1.0, -1.0));
	Box box;
	ColorData cd;
	cd.push_back(glm::vec4(1.0, 1.0, 1.0, 1.0));
	cd.push_back(glm::vec4(0.0, 1.0, 0, 1.0));
	cd.push_back(glm::vec4(0, 0, 1, 1.0));
	cd.push_back(glm::vec4(1.0, 0.0, 0, 1.0));
	Plane plane(Position(0,0,0), Direction(1,0,0), Direction(0,0,1), 12.0f, 12.0f);
	plane.setColorData(cd);

	Text text;
	Button button("", 120.f, 60.f, &window);

//	box.translate(Position(0, -2, 0));
	// run the main loop
	glClearColor(0.4, 0.4, 0.4, 1.0);
	glEnable(GL_DEPTH_TEST);
	
	bool running = true;
	while (running)
	{
		
		physics.update();
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				camera.controller(event.key.code, true);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				camera.controller(event.key.code, false);
			}

			else if (event.type == sf::Event::MouseButtonPressed)
			{
				camera.controller(event.mouseButton.button, true);
			}

			else if (event.type == sf::Event::MouseButtonReleased)
			{
				camera.controller(event.mouseButton.button, false);
			}
			
		}

		camera.doAction();
		
		glEnable(GL_DEPTH_TEST);
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader.getShaderID());
		glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "gPersp"), 1, GL_FALSE, glm::value_ptr(camera.getPerspectiveMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "gWorldToCamera"), 1, GL_FALSE, glm::value_ptr(camera.getWorldToCameraMatrix()));
		glUniform3fv(glGetUniformLocation(shader.getShaderID(), "cameraPosition"), 1, glm::value_ptr(camera.getPosition()));
		glUniform4fv(glGetUniformLocation(shader.getShaderID(), "AmbientColor"), 1, glm::value_ptr(light.getColor()));
		glUniform1f(glGetUniformLocation(shader.getShaderID(), "AmbientIntensity"), light.getIntensity());
		glUniform4fv(glGetUniformLocation(shader.getShaderID(), "DirectionalColor"), 1, glm::value_ptr(dirLight.getColor()));
		glUniform1f(glGetUniformLocation(shader.getShaderID(), "DirectionalIntensity"), dirLight.getIntensity());
		glUniform3fv(glGetUniformLocation(shader.getShaderID(), "DirectionalDirection"), 1, glm::value_ptr(dirLight.getDirection()));
		
		box.Draw(shader.getShaderID());
		plane.Draw(shader.getShaderID());
		text.display(shader2D);
		glBindVertexArray(NULL);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glUseProgram(NULL);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		
		window.display();			
	}

	// release resources...

	return 0;
}