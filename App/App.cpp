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
	ModelLoader loader;
	std::cout <<  loader.load("Rex/Rex.fbx");
	mesh.setPositionData(loader.getPositionData());
	mesh.setNormalData(loader.getNormalData());
	mesh.setIndexData(loader.getIndexData());
	Shader shader;
	shader.loadProgram("simple");
	Camera camera;
	AmbientLight light;
	light.setIntensity(0.1);
	light.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	DirectionalLight dirLight;
	dirLight.setIntensity(0.8);
	dirLight.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	dirLight.setDirection(Direction(0.0, 0.0, 1.0));
	// run the main loop
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
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
		glUniform4fv(glGetUniformLocation(shader.getShaderID(), "AmbientColor"), 1, glm::value_ptr(light.getColor()));
		glUniform1f(glGetUniformLocation(shader.getShaderID(), "AmbientIntensity"), light.getIntensity());
		glUniform4fv(glGetUniformLocation(shader.getShaderID(), "DirectionalColor"), 1, glm::value_ptr(dirLight.getColor()));
		glUniform1f(glGetUniformLocation(shader.getShaderID(), "DirectionalIntensity"), dirLight.getIntensity());
		glUniform3fv(glGetUniformLocation(shader.getShaderID(), "DirectionalDirection"), 1, glm::value_ptr(dirLight.getDirection()));
		mesh.Draw();
		
		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}