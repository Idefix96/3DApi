#include "stdafx.h"
#include "targetver.h"
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
#include "3DMesh\3DMesh.h"
#include "Shader\Shader.h"
#include "Scene\Camera\Camera.h"
#include "3DMesh\ModelLoader.h"
#include "Scene.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Physics\PhysicModel.h"

namespace fs = std::experimental::filesystem;
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
	PhysicModel model;
	model.ApplySphereShape(1.0f, 1.0f, glm::quat(0, 0, 0, 1), glm::vec3(0, 100, 0));
	physics.addPhysicModel(&model);
	window.setActive(true);
	glewInit();
	Shader shader;
	//shader.loadProgram("simple");
	shader.loadProgram("Skeletal");
	Camera camera;
	AmbientLight light;
	light.setIntensity(0.2);
	light.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	DirectionalLight dirLight;
	dirLight.setIntensity(1.0);
	dirLight.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	dirLight.setDirection(Direction(0.0, -1.0, -1.0));
	ModelLoader loader;
	Mesh3D rex;
	loader.load("Rex_sk/Rex.fbx", &rex);
	Scene scene;

	scene.addAmbientLight(&light);
	scene.addDirectionalLight(&dirLight);
	scene.addCamera(&camera);
	scene.addShader(&shader);
	scene.addMesh(&rex, shader.getShaderID());

	// run the main loop
	glClearColor(0.4, 0.4, 0.4, 1.0);
	glEnable(GL_DEPTH_TEST);

	bool running = true;
	sf::Clock timer;
	while (running)
	{	
		rex.Animate(timer.getElapsedTime().asMicroseconds(), "metarig|metarigAction");
		physics.update();
		std::cout << model.getRigidBody()->getWorldTransform().getOrigin().getY() << std::endl;
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

		
		scene.draw();
		ImGui::SFML::Update(window, deltaClock.restart());
		bool open = true;
		ImGui::SetNextWindowPos(ImVec2(20, 20));
		ImGui::SetNextWindowSize(ImVec2(100, 50));
		ImGui::Begin("Sample window", &open, ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize  | ImGuiWindowFlags_NoMove); // begin window
		
		ImGui::Button("Update", ImVec2(100,50));
		if (ImGui::IsItemActive()) {
			rex.rotateBoneGlobal("head", glm::vec3(1, 1, 0), 0.7f);
		}
		ImGui::Separator();
		ImGui::Button("Quit");
		if (ImGui::IsItemClicked()) {
			running = false;
		}
		ImGui::End(); // end window

		ImGui::SFML::Render(window);
		
		//IMPORTANT HERE!
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		window.display();			
	}

	// release resources...
	ImGui::SFML::Shutdown();
	return 0;
}