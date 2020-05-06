/*----------------------------------------
File Name: GraphicEngineApp.h
Purpose: Structure of Graphic Engine App class
Author: Tarn Cooper
Modified: 19 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "FlyCamera.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"

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
	// camera transforms
	FlyCamera* camera;

	aie::ShaderProgram shader;

	aie::Texture gridTexture;

	aie::OBJMesh bunnyMesh;
	aie::OBJMesh buddhaMesh;
	aie::OBJMesh dragonMesh;
	aie::OBJMesh lucyMesh;
	aie::OBJMesh	spearMesh;

	Mesh quadMesh;
	Mesh boxMesh;
	Mesh cylinderMesh;
	Mesh pyramidMesh;
	Mesh coneMesh;
	Mesh gridMesh;
	Mesh sphereMesh;

	glm::mat4 buddhaTransform;
	glm::mat4 bunnyTransform;
	glm::mat4 dragonTransform;
	glm::mat4 lucyTransform;
	glm::mat4 boxTransform;
	glm::mat4 cylinderTransform;
	glm::mat4 quadTransform;
	glm::mat4 pyramidTransform;
	glm::mat4 coneTransform;
	glm::mat4 gridTransform;
	glm::mat4 sphereTransform;
	glm::mat4	spearTransform;

	struct Light {
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;

	};
	Light light;
	glm::vec3 ambientLight;

};