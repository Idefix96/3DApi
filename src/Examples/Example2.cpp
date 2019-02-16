#include "imgui.h"
#include "imgui-SFML.h"

#include <GL\glew.h>

#include <SFML\Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Clock.hpp>
#include "3DMesh\3DMesh.h"
#include "Shader\Shader.h"
#include "Scene\Camera\Camera.h"
#include "3DMesh\ModelLoader.h"
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include "Scene\Light\AmbientLight.h"
#include "Scene\Light\DirectionalLight.h"
#include "Bounding\Box\BoundingBox.h"
#include "BasicBodies\Box\Box.h"
#include "Shapes\BoundingBox.h"
#include "Physics\Physics.h"
#include "BasicBodies\Plane\Plane.h"
#include "GUI\Button\Button.h"
#include "Text\Text.h"
#include "BasicBodies\2D\Box2D\Box2D.h"

int main()
{	
	// create the window
	sf::ContextSettings Settings;
	Settings.depthBits = 24;
	Settings.stencilBits = 8; 
	Settings.antialiasingLevel = 2;
	Settings.majorVersion = 4;
	Settings.minorVersion = 4;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL", sf::Style::Titlebar | sf::Style::Close, Settings);
	//sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL", sf::Style::Default | sf::Style::Close, Settings);
	
	/*IMGUI*/
	ImGui::SFML::Init(window);
	sf::Clock deltaClock;

	window.setVerticalSyncEnabled(true);
	Physics physics;

	window.setActive(true);
	glewInit();
	Shader shader;
	shader.loadProgram("simple");
	Shader shader2D;
	shader2D.loadProgram("2D/Text");
	Shader shader2Dshape;
	shader2Dshape.loadProgram("2D/Sprites");
	Shader bounding;
	bounding.loadProgram("BoundingBodies");
	Camera camera;
	AmbientLight light;
	light.setIntensity(0.2);
	light.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	DirectionalLight dirLight;
	dirLight.setIntensity(1.0);
	dirLight.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	dirLight.setDirection(Direction(0.0, -1.0, -1.0));
	Box box;
	Box2D box2d(0.5f, 0.5f);
	BoundingBox bBox(2.0f, 2.0f);
	Mesh3D rex;
	box2d.translate(Position(0.75, 0.75, 0.0));
	ColorData cd;
	cd.push_back(glm::vec4(1.0, 1.0, 1.0, 1.0));
	cd.push_back(glm::vec4(0.0, 1.0, 0, 1.0));
	cd.push_back(glm::vec4(0, 0, 1, 1.0));
	cd.push_back(glm::vec4(1.0, 0.0, 0, 1.0));
	Plane plane(Position(0,0,0), Direction(1,0,0), Direction(0,0,1), 12.0f, 12.0f);
	plane.setColorData(cd);
	ModelLoader loader;
	loader.load("Rex/Rex.fbx");
	rex.setPositionData(loader.getPositionData());
	rex.setNormalData(loader.getNormalData()); 
	rex.setUVData(loader.getUvData());
	rex.setTangentData(loader.getTangentData());
	rex.setBitangentData(loader.getBitangentData());
	rex.setMaterial(loader.getMaterial()[0]);
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
			ImGui::SFML::ProcessEvent(event);

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
	

		box2d.isClicked(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y,WINDOW_WIDTH, WINDOW_HEIGHT, &window);
	

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
		
		//box.Draw(shader.getShaderID());
		plane.Draw(shader.getShaderID());
		rex.Draw(shader.getShaderID());
		glUseProgram(bounding.getShaderID());
		glUniformMatrix4fv(glGetUniformLocation(bounding.getShaderID(), "gPersp"), 1, GL_FALSE, glm::value_ptr(camera.getPerspectiveMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(bounding.getShaderID(), "gWorldToCamera"), 1, GL_FALSE, glm::value_ptr(camera.getWorldToCameraMatrix()));
		glUniform3fv(glGetUniformLocation(bounding.getShaderID(), "cameraPosition"), 1, glm::value_ptr(camera.getPosition()));
		glUniform4fv(glGetUniformLocation(bounding.getShaderID(), "AmbientColor"), 1, glm::value_ptr(light.getColor()));
		glUniform1f(glGetUniformLocation(bounding.getShaderID(), "AmbientIntensity"), light.getIntensity());
		glUniform4fv(glGetUniformLocation(bounding.getShaderID(), "DirectionalColor"), 1, glm::value_ptr(dirLight.getColor()));
		glUniform1f(glGetUniformLocation(bounding.getShaderID(), "DirectionalIntensity"), dirLight.getIntensity());
		glUniform3fv(glGetUniformLocation(bounding.getShaderID(), "DirectionalDirection"), 1, glm::value_ptr(dirLight.getDirection()));
		bBox.Draw(bounding.getShaderID());
		glUseProgram(shader2Dshape.getShaderID());

		
		box2d.display(shader2Dshape.getShaderID(), shader2D.getShaderID(), window.getSize().x, window.getSize().y);
		
		glBindVertexArray(NULL);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glUseProgram(NULL);

		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::Begin("Sample window"); // begin window

		ImGui::End(); // end window

		ImGui::SFML::Render(window);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		
		window.display();			
	}

	// release resources...
	ImGui::SFML::Shutdown();
	return 0;
}