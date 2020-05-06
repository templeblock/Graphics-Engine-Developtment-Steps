/*----------------------------------------
File Name: GraphicEngineApp.h
Purpose: Functions used by Graphic Engine App class
Author: Tarn Cooper
Modified: 17 April 2020
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
}
//-----------------------------------------------------------
// Destructs graphic engine app
//-----------------------------------------------------------
GraphicsEngineApp::~GraphicsEngineApp() {}
//-----------------------------------------------------------
// Sets intitial values on start up
//-----------------------------------------------------------
bool GraphicsEngineApp::startup() 
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);
	
	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);
	// create simple camera transforms
	camera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	camera->SetLookAt(vec3(10), vec3(0), vec3(0, 1, 0));
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
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}
//-----------------------------------------------------------
// Draws objects on screen
//-----------------------------------------------------------
void GraphicsEngineApp::draw() 
{
	// wipe the screen to the background colour
	clearScreen();
	Gizmos::draw(camera->GetProjectView());
}