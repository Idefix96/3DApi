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
int main()
{
	// create the window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);
	Physics physics;
	// activate the window
	window.setActive(true);
	glewInit();
	PositionData pd;
	pd.push_back(Position(0,0,0));
	pd.push_back(Position(1, 1, 0));
	pd.push_back(Position(-1, 1, 0));
	NormalData nd;
	nd.push_back(Direction(0,0, 1));
	nd.push_back(Direction(-2, -2, 1));
	nd.push_back(Direction(3, 3, 1));
	Mesh3D mesh;
	Mesh3D triangle;
	triangle.setPositionData(pd);
	triangle.setNormalData(nd);
	ModelLoader loader;
	loader.load("Rex/Rex.fbx");
	mesh.setPositionData(loader.getPositionData());
	mesh.setNormalData(loader.getNormalData());
	mesh.setIndexData(loader.getIndexData());
	mesh.setUVData(loader.getUvData());
	mesh.setTangentData(loader.getTangentData());
	mesh.setBitangentData(loader.getBitangentData());
	mesh.setMaterial(loader.getMaterial()[0]);
	//mesh.translate(Position(0, -2, 0));
	Shader shader;
	shader.loadProgram("simple");
	Camera camera;
	AmbientLight light;
	light.setIntensity(0.3);
	light.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	DirectionalLight dirLight;
	dirLight.setIntensity(1.0);
	dirLight.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	dirLight.setDirection(Direction(0.0, -1.0, -1.0));
	Box box;
	Plane plane(Position(0,0,0), Direction(1,0,0), Direction(0,0,1), 2.0f, 2.0f);
//	box.translate(Position(0, -2, 0));
	// run the main loop
	glClearColor(0.4, 0.4, 0.4, 1.0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
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
		glUniform3fv(glGetUniformLocation(shader.getShaderID(), "cameraPosition"), 1, glm::value_ptr(camera.getPosition()));
		glUniform4fv(glGetUniformLocation(shader.getShaderID(), "AmbientColor"), 1, glm::value_ptr(light.getColor()));
		glUniform1f(glGetUniformLocation(shader.getShaderID(), "AmbientIntensity"), light.getIntensity());
		glUniform4fv(glGetUniformLocation(shader.getShaderID(), "DirectionalColor"), 1, glm::value_ptr(dirLight.getColor()));
		glUniform1f(glGetUniformLocation(shader.getShaderID(), "DirectionalIntensity"), dirLight.getIntensity());
		glUniform3fv(glGetUniformLocation(shader.getShaderID(), "DirectionalDirection"), 1, glm::value_ptr(dirLight.getDirection()));
	
			mesh.Draw(shader.getShaderID());
			box.Draw(shader.getShaderID());
			plane.Draw(shader.getShaderID());
		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}