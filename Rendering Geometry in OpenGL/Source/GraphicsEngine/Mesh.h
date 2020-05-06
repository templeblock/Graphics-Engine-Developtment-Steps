/*----------------------------------------
File Name: Mesh.h
Purpose: Structure of Mesh class
Author: Tarn Cooper
Modified: 17 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <glm/glm.hpp>
//Mesh Class
class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	struct Vertex {
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};
	int MakeTri(glm::vec4 positon1, glm::vec4 positon2, glm::vec4 positon3, Vertex vertices[], int count);
	int MakeQuad(glm::vec4 positon1, glm::vec4 positon2, glm::vec4 positon3, glm::vec4 positon4, Vertex vertices[], int count);
	int MakeDisc(glm::vec3 position, float radius, Vertex vertices[], int count);
	void InitialiseQuad(float width, float length, glm::vec3 center = glm::vec3(0));
	void InitialiseBox(float width, float height, float length, glm::vec3 center = glm::vec3(0));
	void InitialiseSphere(float radius, glm::vec3 center = glm::vec3(0));
	void InitialiseDisc(float radius, glm::vec3 center = glm::vec3(0));
	void InitialiseCylinder(float height, float radius, glm::vec3 center = glm::vec3(0));
	void InitialisePyramid(float width, float height, float length, glm::vec3 center = glm::vec3(0));
	void InitialiseCone(float radius, float height, glm::vec3 center = glm::vec3(0));
	void InitialiseGrid(float width, float length, int columns, int rows, glm::vec3 center = glm::vec3(0));
	void Initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr);

	virtual void Draw();
protected:
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};
