/*----------------------------------------
File Name: GraphicEngineApp.cpp
Purpose: Functions of Graphic Engine App class
Author: Tarn Cooper
Modified: 18 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "GraphicsEngineApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;
//-----------------------------------------------------------
// Constructs graphic engine app
//-----------------------------------------------------------
GraphicsEngineApp::GraphicsEngineApp()
{
	camera = new FlyCamera();
	boxTransform = glm::mat4(0);
	buddhaTransform = glm::mat4(0);
	bunnyTransform = glm::mat4(0);
	coneTransform = glm::mat4(0);
	cylinderTransform = glm::mat4(0);
	dragonTransform = glm::mat4(0);
	gridTransform = glm::mat4(0);
	lucyTransform = glm::mat4(0);
	pyramidTransform = glm::mat4(0);
	quadTransform = glm::mat4(0);
	sphereTransform = glm::mat4(0);
}

//-----------------------------------------------------------
// Destructs graphic engine app
//-----------------------------------------------------------
GraphicsEngineApp::~GraphicsEngineApp() {}

bool GraphicsEngineApp::startup() 
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);
	camera = new FlyCamera();
	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms

	camera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	camera->SetLookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	camera->SetSpeed(10);

	shader.loadShader(aie::eShaderStage::VERTEX, "../bin/Shader/simple.vert");
	shader.loadShader(aie::eShaderStage::FRAGMENT, "../bin/Shader/simple.frag");

	
	if (shader.link() == false)
	{
		printf("Shader Error: %s\n", shader.getLastError());
		return false;
	}

	if (bunnyMesh.load("../bin/Models/bunny.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
		return false;

	}

	if (buddhaMesh.load("../bin/Models/Buddha.obj") == false)
	{
		printf("Buddha Mesh Error!\n");
		return false;

	}

	if (dragonMesh.load("../bin/Models/Dragon.obj") == false)
	{
		printf("Dragon Mesh Error!\n"); 
		return false;

	}

	if (lucyMesh.load("../bin/Models/Lucy.obj") == false)
	{
		printf("Lucy Mesh Error!\n");
		return false;

	}

	quadMesh.InitialiseQuad(5,5);
	quadTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1
	};

	boxMesh.InitialiseBox(5,5,5);
	boxTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-10, 0, -10, 1
	};

	cylinderMesh.InitialiseCylinder(5, 2.5f);
	cylinderTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, -10, 1
	};

	pyramidMesh.InitialisePyramid(5, 5, 5);
	pyramidTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-5, 0, -10, 1
	};

	coneMesh.InitialiseCone(2.5f, 5);
	coneTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		5, 0, -10, 1
	};

	gridMesh.InitialiseGrid(1, 1, 2, 2);
	gridTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
};

	sphereMesh.InitialiseSphere(2.5f);
	sphereTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		10, 0, -10, 1
	};


	bunnyTransform = {
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		-10, 0, 10, 1
	};

	buddhaTransform = {
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		-5, 0, 10, 1
	};

	dragonTransform = {
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		5, 0, 10, 1
	};

	lucyTransform = {
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		10, 0, 10, 1
	};

	return true;
}

//-----------------------------------------------------------
// Destroys pointers on shutdown
//-----------------------------------------------------------
void GraphicsEngineApp::shutdown() {
	delete camera;
	Gizmos::destroy();
}
//-----------------------------------------------------------
// Updates graphic engine app each frame
// deltaTime (float): What is the deltaTime?
//-----------------------------------------------------------
void GraphicsEngineApp::update(float deltaTime)
{
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	camera->Update(deltaTime);
	// quit if we press escape
	aie::Input * input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}
//-----------------------------------------------------------
// Draws objects on screen
//-----------------------------------------------------------
void GraphicsEngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	shader.bind();

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * bunnyTransform);
	bunnyMesh.draw();

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * lucyTransform);
	lucyMesh.draw();

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * buddhaTransform);
	buddhaMesh.draw();

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * dragonTransform);
	dragonMesh.draw();

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * boxTransform);
	boxMesh.Draw();

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * coneTransform);
	coneMesh.Draw();

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * pyramidTransform);
	pyramidMesh.Draw();

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * sphereTransform);
	sphereMesh.Draw();

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * cylinderTransform);
	cylinderMesh.Draw();

	

	Gizmos::draw(camera->GetProjectView());
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());

}