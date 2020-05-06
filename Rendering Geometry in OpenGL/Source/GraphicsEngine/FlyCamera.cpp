/*----------------------------------------
File Name: FlyCamera.cpp
Purpose: Functions of Fly Camera class
Author: Tarn Cooper
Modified: 17 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "FlyCamera.h"
#include <Input.h>
#include <glm/ext.hpp>
//-----------------------------------------------------------
// Constructs Fly Camera Class
//-----------------------------------------------------------
FlyCamera::FlyCamera() : Camera()
{
	speed = 3;
	up = glm::vec3(0, 1, 0);
}
//-----------------------------------------------------------
// Updates Fly Camera Class
// deltaTime (float): What is the delta time?
//-----------------------------------------------------------
void FlyCamera::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	float currentSpeed;
	//Adds turbo to camera
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
	{
		currentSpeed = speed * 2;
	}
	else
	{
		currentSpeed = speed;
	}

	//Control Movement based on direction of camera using wasd keys
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		SetPosition(GetWorldTransform()[3] + glm::normalize(-GetWorldTransform()[2]) * (currentSpeed * deltaTime));
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		SetPosition(GetWorldTransform()[3] + glm::normalize(GetWorldTransform()[2]) * (currentSpeed * deltaTime));
	}
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		SetPosition(GetWorldTransform()[3] + glm::normalize(-GetWorldTransform()[0]) * (currentSpeed * deltaTime));
	}
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		SetPosition(GetWorldTransform()[3] + glm::normalize(GetWorldTransform()[0]) * (currentSpeed * deltaTime));
	}

	//Control rotaion of camera using mouse mouse movement
	glm::mat4 rotation = glm::mat4(1.0f);
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		rotation = glm::rotate(rotation, -input->getMouseDeltaX() * deltaTime, glm::vec3(0, 1, 0));
		rotation = glm::rotate(rotation, input->getMouseDeltaY() * deltaTime, glm::vec3(1, 0, 0));
		SetWorldTransform(GetWorldTransform() * rotation);
	}
	//Control rotaion of camera using direction keys
	else
	{
		if (input->isKeyDown(aie::INPUT_KEY_UP))
		{
			rotation = glm::rotate(rotation, speed * deltaTime, glm::vec3(1, 0, 0));
		}
		if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		{
			rotation = glm::rotate(rotation, -speed * deltaTime, glm::vec3(1, 0, 0));
		}
		if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		{
			rotation = glm::rotate(rotation, speed * deltaTime, glm::vec3(0, 1, 0));
		}
		if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		{
			rotation = glm::rotate(rotation, -speed * deltaTime, glm::vec3(0, 1, 0));
		}
		SetWorldTransform(GetWorldTransform() * rotation);
	}

	//Straighten Camera to prevent roation on z-axis of camera
	glm::mat4 transform = GetWorldTransform();
	transform[0] = glm::vec4(glm::normalize(glm::cross(glm::vec3(0, 1, 0), glm::vec3(transform[2].x, transform[2].y, transform[2].z))), 0);
	transform[1] = glm::vec4(glm::normalize(glm::cross(-glm::vec3(transform[0].x, transform[0].y, transform[0].z), glm::vec3(transform[2].x, transform[2].y, transform[2].z))), 0);
	SetWorldTransform(transform);

	UpdateProjectionViewTransfrom();
}

//-----------------------------------------------------------
// Sets speed of fly camera
// speed (float): What is the speed of camera?
//-----------------------------------------------------------
void FlyCamera::SetSpeed(float speed)
{
	this->speed = speed;
}