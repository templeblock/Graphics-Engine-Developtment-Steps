/*----------------------------------------
File Name: Camera.cpp
Purpose: Functions of Camera class
Author: Tarn Cooper
Modified: 17 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Camera.h"
#include <glm/ext.hpp>
//-----------------------------------------------------------
// Constructs Camera Class
//-----------------------------------------------------------
Camera::Camera()
{
	projectionTransform = glm::mat4(0);
	projectionViewTransform = glm::mat4(0);
	viewTransform = glm::mat4(0);
	worldTransform = glm::mat4(0);
}
//-----------------------------------------------------------
// Sets Projection Transform using persepective function
// fieldOfView (float): What is the field of view?
// aspectRatio (float): What is the aspect ratio?
// near (float): What is near camera cut-off?
// far (float): What is far camera cut-off?
//-----------------------------------------------------------
void Camera::SetPerspective(float fieldOfView, float aspectRatio, float near, float far)
{
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, near, far);
}
//-----------------------------------------------------------
// Sets View Transform using lookat function
// from (glm::vec3): Where is it looking from?
// to (glm::vec3): Where is it looking to?
// up (glm::vec3): What direction is up?
//-----------------------------------------------------------
void Camera::SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	viewTransform = glm::lookAt(from, to, up);
	worldTransform = glm::inverse(viewTransform);
}
//-----------------------------------------------------------
// Sets position of camera
// position (glm::vec3): What is the position of camera?
//-----------------------------------------------------------
void Camera::SetPosition(glm::vec3 position)
{
	worldTransform[3] = glm::vec4(position, 1);
}
//-----------------------------------------------------------
// Gets World Tranform of camera
// return (glm::mat4): Returns the World Tranform of camera
//-----------------------------------------------------------
glm::mat4 Camera::GetWorldTransform()
{
	return worldTransform;
}
//-----------------------------------------------------------
// Gets View Tranform of camera
// return (glm::mat4): Returns the View Tranform of camera
//-----------------------------------------------------------
glm::mat4 Camera::GetView()
{
	return viewTransform;
}
//-----------------------------------------------------------
// Gets Projection Tranform of camera
// return (glm::mat4): Returns the Projection Tranform of camera
//-----------------------------------------------------------
glm::mat4 Camera::GetProjection()
{
	return projectionTransform;
}
//-----------------------------------------------------------
// Gets Projection View Tranform of camera
// return (glm::mat4): Returns the Projection View Tranform of camera
//-----------------------------------------------------------
glm::mat4 Camera::GetProjectView()
{
	return projectionViewTransform;
}
//-----------------------------------------------------------
// Updates Projection View Transform of camera
//-----------------------------------------------------------
void Camera::UpdateProjectionViewTransfrom()
{
	viewTransform = glm::inverse(worldTransform);
	projectionViewTransform = projectionTransform * viewTransform;
}
//-----------------------------------------------------------
// Sets World Transform of camera
// transform (glm::mat4): What is the new world transform?
//-----------------------------------------------------------
void Camera::SetWorldTransform(glm::mat4 transform)
{
	worldTransform = transform;
}