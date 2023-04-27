#pragma once
#include "pch.h"
#include "SphereGPUProgram.h"
float pi = 3.1415926535897932384626433832795f;
SphereGPUProgram::SphereGPUProgram()
{
}


SphereGPUProgram::~SphereGPUProgram()
{
}
bool SphereGPUProgram::bindVertieces(VertexGenerator& vGen, float dT, float wT)
{
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	
	//float p[7] = { -pi / 2, pi / 2, pi / 20, -pi, pi, pi / 20, 1 };	//SFERA
	//float p[7] = { 0, 2*pi, pi / 20, -pi/2, pi/2, pi / 20, 1 };		//KLEPSYDRA
	float p[7] = { 0, pi, pi / 20, -pi/2, pi/2, pi / 20, 1 };			//MUSZLA
	float* vertices = vGen.generateVertieces(p);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vGen.Size()*vGen.Count()*vGen.Dim() * sizeof(float), vertices, GL_STATIC_DRAW);
	// position atribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//type attribute
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glUseProgram(shaderProgram);
	delete[] vertices;
	return true;
}