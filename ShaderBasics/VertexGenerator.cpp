#include "pch.h"
#include "VertexGenerator.h"
#include <iostream>

void VertexGenerator::generateOneVertex(float * vertices, int & index, float x, float y, float z, float r, float g, float b, bool type)
{
	
	vertices[index] = x;
	vertices[++index] = y;
	vertices[++index] = z;
	//col
	vertices[++index] = r;
	vertices[++index] = g;
	vertices[++index] = b;
	vertices[++index] = 1;
	//kind
	if (type)
		vertices[++index] = 1;
	else
		vertices[++index] = 0;

	index += 1;
}

float * VertexGenerator::generateVertieces(float* params)
{
	float xStart = params[0];  
	float xEnd = params[1]; 
	float xStep = params[2];
	float zStart = params[3]; 
	float zEnd = params[4];
	float zStep = params[5];
	float lineDensity = params[6];
	size = (int)((xEnd - xStart) / xStep) * (int)((zEnd - zStart) / zStep);
	quadSize = size;
	size += (int)((xEnd - xStart) / (lineDensity*xStep)) * (int)((zEnd - zStart) / (lineDensity*zStep));
	count = 4;																				//cztery wierzcho³ki
	dim = 8;
	float *vertices = new float[size*count*dim];
	int i = 0;
	bool type = false;
	for (float x = xStart; x < xEnd; x += xStep) {
		for (float z = zStart; z < zEnd; z += zStep) {

			generateOneVertex(vertices, i, x, 0, z, 0, 0, 1, type);
			generateOneVertex(vertices, i, x + xStep, 0, z, 0, 0, 1, type);
			generateOneVertex(vertices, i, x + xStep, 0, z + zStep, 0, 0, 1, type);			//cztery wierzcho³ki na potrzebê generowania kwadratów
			generateOneVertex(vertices, i, x, 0, z + zStep, 0, 0, 1, type);
			type = !type;
			//generateOneVertex(vertices, i, x, 0, z, 0, 0, 1, type);
			//generateOneVertex(vertices, i, x + xStep, 0, z + zStep, 0, 0, 1, type);
			//generateOneVertex(vertices, i, x, 0, z + zStep, 0, 0, 1, type);
			//type = !type;

		}
	}

	for (float x = xStart; x < xEnd; x += xStep * lineDensity) {
		for (float z = zStart; z < zEnd; z += zStep * lineDensity) {

			generateOneVertex(vertices, i, x, 0, z, 1, 1, 1, false);
			generateOneVertex(vertices, i, x + lineDensity * xStep, 0, z, 1, 1, 1, false);



			generateOneVertex(vertices, i, x, 0, z, 1, 1, 1, false);
			generateOneVertex(vertices, i, x, 0, z + lineDensity * zStep, 1, 1, 1, false);

		}
	}

	std::cout << "\nGenerated vertices number:" << i << "\n";
	return vertices;
}


VertexGenerator::VertexGenerator()
{

}


VertexGenerator::~VertexGenerator()
{
}
