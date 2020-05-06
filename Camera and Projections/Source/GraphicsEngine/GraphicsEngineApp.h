/*----------------------------------------
File Name: GraphicEngineApp.h
Purpose: Structure of Graphic Engine App class
Author: Tarn Cooper
Modified: 17 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Application.h"
#include <glm/mat4x4.hpp>
#include "FlyCamera.h"

//Graphic Engine App Class
class GraphicsEngineApp : public aie::Application {
public:

	GraphicsEngineApp();
	virtual ~GraphicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	FlyCamera* camera;
};