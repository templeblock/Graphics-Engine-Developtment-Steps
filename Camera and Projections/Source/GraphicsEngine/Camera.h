/*----------------------------------------
File Name: Camera.h
Purpose: Structure of Camera class
Author: Tarn Cooper
Modified: 17 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <glm/glm.hpp>
//Camera Class
class Camera
{
public:
	Camera();
	virtual void Update(float deltaTime) = 0;
	void SetPerspective(float fieldOfView, float aspectRatio, float near, float far);
	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void SetPosition(glm::vec3 position);
	glm::mat4 GetWorldTransform();
	glm::mat4 GetView();
	glm::mat4 GetProjection();
	glm::mat4 GetProjectView();
	void UpdateProjectionViewTransfrom();
	void SetWorldTransform(glm::mat4 transform);

private:
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
};

