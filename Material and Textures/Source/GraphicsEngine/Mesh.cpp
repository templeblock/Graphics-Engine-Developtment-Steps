/*----------------------------------------
File Name: Mesh.cpp
Purpose: Functions of mesh class
Author: Tarn Cooper
Modified: 18 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Mesh.h"
#include <gl_core_4_4.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

//-----------------------------------------------------------
// Constructs Mesh class
//-----------------------------------------------------------
Mesh::Mesh()
{
	triCount = 0;
	vao = 0;
	vbo = 0;
	ibo = 0;
}

//-----------------------------------------------------------
// Destructs Mesh class
//-----------------------------------------------------------
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}
//-----------------------------------------------------------
// Makes a triangle mesh
// position0 (glm::vec4): What is the first point position?
// position1 (glm::vec4): What is the second point position?
// position2 (glm::vec4): What is the third point position?
// vertices (Vertex[]): What is the array of vertex?
// count (int): How many Vertex are in array?
//-----------------------------------------------------------
int Mesh::MakeTri(glm::vec4 positon0, glm::vec4 positon1, glm::vec4 positon2, Vertex vertices[], int count)
{
	int startCount = count;

	vertices[count++] = Vertex{ positon0 };
	vertices[count++] = Vertex{ positon1 };
	vertices[count++] = Vertex{ positon2 };

	if (startCount % 2 == 0)
	{
		vertices[startCount + 0].texCoord = { 0, 0 };
		vertices[startCount + 1].texCoord = { 1, 0 };
		vertices[startCount + 2].texCoord = { 0, 1 };
	}
	else
	{
		vertices[startCount + 0].texCoord = { 0, 1 };
		vertices[startCount + 1].texCoord = { 1, 0 };
		vertices[startCount + 2].texCoord = { 1, 1 };
	}

	return count;
}

//-----------------------------------------------------------
// Makes a quad mesh
// position0 (glm::vec4): What is the first point position?
// position1 (glm::vec4): What is the second point position?
// position2 (glm::vec4): What is the third point position?
// position3 (glm::vec4): What is the fourth point position?
// vertices (Vertex[]): What is the array of vertex?
// count (int): How many Vertex are in array?
//-----------------------------------------------------------
int Mesh::MakeQuad(glm::vec4 positon0, glm::vec4 positon1, glm::vec4 positon2, glm::vec4 positon3, Vertex vertices[], int count)
{
	int startCount = count;

	count = MakeTri(positon1, positon0, positon3, vertices, count);
	count = MakeTri(positon3, positon0, positon2, vertices, count);

	return count;
}

//-----------------------------------------------------------
// Makes a disc mesh
// position (glm::vec4): What is the position?
// vertices (Vertex[]): What is the array of vertex?
// count (int): How many Vertex are in array?
//-----------------------------------------------------------
int Mesh::MakeDisc(glm::vec3 position, float radius, Vertex vertices[], int count)
{
	int segments = 10;
	float segmentSize = (2 * glm::pi<float>()) / segments;
	glm::vec4 position0 = glm::vec4(position, 1);
	glm::vec4 position1;
	glm::vec4 position2;
	for (int i = 0; i < segments; ++i)
	{
		position1 = glm::vec4(glm::sin(i * segmentSize) * radius, position.y, glm::cos(i * segmentSize) * radius, 1);
		position2 = glm::vec4(glm::sin((i + 1) * segmentSize) * radius, position.y, glm::cos((i + 1) * segmentSize) * radius, 1);
		count = MakeTri(position0, position1, position2, vertices, count);
	}
	return count;
}

//-----------------------------------------------------------
// Makes and initializes a disc mesh
// radius (float): What is the radius of disk?
// center (glm:vec3): Where is center of disk?
//-----------------------------------------------------------
void Mesh::InitialiseDisc(float radius, glm::vec3 center)
{
	const int size = 30;
	int segments = 10;
	float segmentSize = (2 * glm::pi<float>()) / segments;
	Vertex vertices[size];
	int count = 0;
	glm::vec4 position0 = glm::vec4(center, 1);
	glm::vec4 position1;
	glm::vec4 position2;
	for (int i = 0; i < segments; ++i)
	{
		position1 = glm::vec4(glm::sin(i * segmentSize) * radius, center.y, glm::cos(i * segmentSize) * radius, 1);
		position2 = glm::vec4(glm::sin((i + 1) * segmentSize) * radius, center.y, glm::cos((i + 1) * segmentSize) * radius, 1);
		count = MakeTri(position0, position1, position2, vertices, count);
	}
	Initialise(count, vertices);

}

//-----------------------------------------------------------
// Makes and initializes a quad mesh
// width (float): What is the width of quad?
// length (float): What is the length of quad?
// center (glm:vec3): Where is center of quad?
//-----------------------------------------------------------
void Mesh::InitialiseQuad(float width, float length, glm::vec3 center)
{
	const int size = 6;
	Vertex vertices[size];
	int count = 0;

	glm::vec4 position0 = { center.x + width / 2, center.y, center.z + length / 2, 1 };
	glm::vec4 position1 = { center.x - width / 2, center.y,center.z + length / 2, 1 };
	glm::vec4 position2 = { center.x + width / 2, center.y,center.z - length / 2, 1 };
	glm::vec4 position3 = { center.x - width / 2, center.y,center.z - length / 2, 1 };

	count = MakeTri(position1, position0, position3, vertices, count);
	count = MakeTri(position3, position0, position2, vertices, count);

	Initialise(size, vertices);
}

//-----------------------------------------------------------
// Makes and initializes a cube mesh
// width (float): What is the width of cube?
// length (float): What is the length of cube?
// height (float): What is the height of cube?
// center (glm:vec3): Where is center of cube?
//-----------------------------------------------------------
void Mesh::InitialiseBox(float width, float height, float length, glm::vec3 center)
{
	const int size = 6 * 6;
	Vertex vertices[size];
	int count = 0;

	glm::vec4 position0 = { center.x + width / 2, center.y + height / 2, center.z + length / 2, 1 };
	glm::vec4 position1 = { center.x - width / 2, center.y + height / 2,center.z + length / 2, 1 };
	glm::vec4 position2 = { center.x + width / 2, center.y + height / 2,center.z - length / 2, 1 };
	glm::vec4 position3 = { center.x - width / 2, center.y + height / 2,center.z - length / 2, 1 };

	glm::vec4 position4 = { center.x + width / 2, center.y - height / 2, center.z + length / 2, 1 };
	glm::vec4 position5 = { center.x - width / 2, center.y - height / 2,center.z + length / 2, 1 };
	glm::vec4 position6 = { center.x + width / 2, center.y - height / 2,center.z - length / 2, 1 };
	glm::vec4 position7 = { center.x - width / 2, center.y - height / 2,center.z - length / 2, 1 };

	//Top
	count = MakeQuad(position0, position1, position2, position3, vertices, count);

	//Bottom
	count = MakeQuad(position5, position4, position7, position6, vertices, count);

	//Left
	count = MakeQuad(position0, position2, position4, position6, vertices, count);

	//Forward
	count = MakeQuad(position1, position0, position5, position4, vertices, count);

	//Back
	count = MakeQuad(position2, position3, position6, position7, vertices, count);

	//Right
	count = MakeQuad(position3, position1, position7, position5, vertices, count);

	Initialise(size, vertices);

}

//-----------------------------------------------------------
// Makes and initializes a cylinder mesh
// radius (float): What is the radius of cylidner?
// height (float): What is the height of cylinder?
// center (glm:vec3): Where is center of cylinder?
//-----------------------------------------------------------
void Mesh::InitialiseCylinder(float height, float radius, glm::vec3 center)
{
	const int size = 120;
	int segments = 10;
	float segmentSize = (2 * glm::pi<float>()) / segments;
	Vertex vertices[size];
	int count = 0;
	glm::vec4 position0 = glm::vec4(center.x, center.y + height / 2, center.z, 1);
	glm::vec4 position1 = glm::vec4(center.x, center.y - height / 2, center.z, 1);
	glm::vec4 position2;
	glm::vec4 position3;
	glm::vec4 position4;
	glm::vec4 position5;
	for (int i = 0; i < segments; ++i)
	{
		//Top Disk
		position2 = glm::vec4(glm::sin(i * segmentSize) * radius, position0.y, glm::cos(i * segmentSize) * radius, 1);
		position3 = glm::vec4(glm::sin((i + 1) * segmentSize) * radius, position0.y, glm::cos((i + 1) * segmentSize) * radius, 1);

		//Bottom Disk
		position4 = glm::vec4(glm::sin(i * segmentSize) * radius, position1.y, glm::cos(i * segmentSize) * radius, 1);
		position5 = glm::vec4(glm::sin((i + 1) * segmentSize) * radius, position1.y, glm::cos((i + 1) * segmentSize) * radius, 1);

		//Create
		count = MakeTri(position0, position2, position3, vertices, count);
		count = MakeTri(position1, position5, position4, vertices, count);
		count = MakeQuad(position2, position3, position4, position5, vertices, count);

	}
	Initialise(count, vertices);
}

//-----------------------------------------------------------
// Makes and initializes a sphere mesh
// radius (float): What is the radius of sphere?
// center (glm:vec3): Where is center of sphere?
//-----------------------------------------------------------
void Mesh::InitialiseSphere(float radius, glm::vec3 center)
{
	const int size = 300;
	int sectorCount = 6;
	int stackCount = 6;

	float sectorStep = 2 * glm::pi<float>() / sectorCount;
	float stackStep = glm::pi<float>() / stackCount;
	float sectorAngle, sectorAngleAlt;
	float stackAngle, stackAngleAlt;

	Vertex vertices[size];
	int count = 0;
	glm::vec4 position0;
	glm::vec4 position1;
	glm::vec4 position2;
	glm::vec4 position3;

	//Does each stack
	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = glm::pi<float>() / 2 - i * stackStep;
		stackAngleAlt = glm::pi<float>() / 2 - (i + 1) * stackStep;
		//Does each sector
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;
			sectorAngleAlt = (j + 1) * sectorStep;

			position0 = glm::vec4(radius * glm::cos(stackAngle) * glm::cos(sectorAngle), radius * glm::cos(stackAngle) * glm::sin(sectorAngle), radius * glm::sin(stackAngle), 1);
			position1 = glm::vec4(radius * glm::cos(stackAngle) * glm::cos(sectorAngleAlt), radius * glm::cos(stackAngle) * glm::sin(sectorAngleAlt), radius * glm::sin(stackAngle), 1);
			position2 = glm::vec4(radius * glm::cos(stackAngleAlt) * glm::cos(sectorAngle), radius * glm::cos(stackAngleAlt) * glm::sin(sectorAngle), radius * glm::sin(stackAngleAlt), 1);
			position3 = glm::vec4(radius * glm::cos(stackAngleAlt) * glm::cos(sectorAngleAlt), radius * glm::cos(stackAngleAlt) * glm::sin(sectorAngleAlt), radius * glm::sin(stackAngleAlt), 1);

			if (i != 0)
			{
				count = MakeTri(position1, position0, position2, vertices, count);
			}
			if (i != (stackCount))
			{
				count = MakeTri(position1, position2, position3, vertices, count);
			}
		}

	}

	Initialise(count, vertices);
}

//-----------------------------------------------------------
// Makes and initializes a pyramid mesh
// width (float): What is the width of pyramid?
// height (float): What is the height of pyramid?
// length (float): What is the length of pyramid?
// center (glm:vec3): Where is center of pyramid?
//-----------------------------------------------------------
void Mesh::InitialisePyramid(float width, float height, float length, glm::vec3 center)
{
	const int size = 6 * 6;
	Vertex vertices[size];
	int count = 0;
	//Base
	glm::vec4 position0 = { center.x + width / 2, center.y - height / 2, center.z + length / 2, 1 };
	glm::vec4 position1 = { center.x - width / 2, center.y - height / 2,center.z + length / 2, 1 };
	glm::vec4 position2 = { center.x + width / 2, center.y - height / 2,center.z - length / 2, 1 };
	glm::vec4 position3 = { center.x - width / 2, center.y - height / 2,center.z - length / 2, 1 };

	//Tip
	glm::vec4 position4 = { center.x, center.y + height / 2, center.z,  1 };

	//Bottom
	count = MakeQuad(position1, position0, position3, position2, vertices, count);
	count = MakeTri(position4, position1, position0, vertices, count);
	count = MakeTri(position4, position0, position2, vertices, count);
	count = MakeTri(position4, position2, position3, vertices, count);
	count = MakeTri(position4, position3, position1, vertices, count);
	Initialise(count, vertices);
}

//-----------------------------------------------------------
// Makes and initializes a cone mesh
// height (float): What is the height of cone?
// radius (float): What is the radius of cone?
// center (glm:vec3): Where is center of cone?
//-----------------------------------------------------------
void Mesh::InitialiseCone(float radius, float height, glm::vec3 center)
{
	const int size = 120;
	int segments = 10;
	float segmentSize = (2 * glm::pi<float>()) / segments;
	Vertex vertices[size];
	int count = 0;
	glm::vec4 position0;
	glm::vec4 position1;
	glm::vec4 position2 = { center.x, center.y + height / 2, center.z,  1 };
	glm::vec4 position3 = { center.x, center.y - height / 2, center.z,  1 };

	for (int i = 0; i < segments; ++i)
	{
		//Bottom Disk
		position0 = glm::vec4(glm::sin(i * segmentSize) * radius, center.y - height / 2, glm::cos(i * segmentSize) * radius, 1);
		position1 = glm::vec4(glm::sin((i + 1) * segmentSize) * radius, center.y - height / 2, glm::cos((i + 1) * segmentSize) * radius, 1);

		count = MakeTri(position3, position1, position0, vertices, count);
		count = MakeTri(position2, position0, position1, vertices, count);
	}
	Initialise(count, vertices);
}

//-----------------------------------------------------------
// Makes and initializes a grid mesh
// width (float): What is the width of grid?
// length (float): What is the length of grid?
// columns (int): How many in columns?
// width (float): How many in columns?
// center (glm:vec3): Where is center of grid?
//-----------------------------------------------------------
void Mesh::InitialiseGrid(float width, float length, int columns, int rows, glm::vec3 center)
{
	const int size = 24;
	Vertex vertices[size];
	int count = 0;

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			glm::vec4 position0 = glm::vec4(center.x + (i * width), center.y, center.z + (j * length), 1);
			glm::vec4 position1 = glm::vec4(center.x + ((i + 1) * width), center.y, center.z + ((j)* length), 1);
			glm::vec4 position2 = glm::vec4(center.x + (i * width), center.y, center.z + ((j + 1) * length), 1);
			glm::vec4 position3 = glm::vec4(center.x + ((i + 1) * width), center.y, center.z + ((j + 1) * length), 1);

			count = MakeQuad(position0, position1, position2, position3, vertices, count);
		}
	}
	Initialise(count, vertices);
}

//-----------------------------------------------------------
// Draws mesh to screen
//-----------------------------------------------------------
void Mesh::Draw()
{
	glBindVertexArray(vao);

	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}

//-----------------------------------------------------------
// Initialises through each point to create mesh
// vertexCount (unsigned int): How many vertices?
// vertices (const Vertex*): What is the pointer to vertices array?
// indexCount (unsigned int): How many indices?
// indices (const Vertex*): What is the pointer to indices array?
//-----------------------------------------------------------
void Mesh::Initialise(unsigned int vertexCount, const Vertex * vertices, unsigned int indexCount, unsigned int* indices)
{
	assert(vao == 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)32);

	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	}
	else
	{
		triCount = vertexCount / 3;
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}