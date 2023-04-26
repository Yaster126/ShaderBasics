#pragma once
class VertexGenerator
{
private:
	int size = 0;
	int quadSize = 0;
	void generateOneVertex(float * vertices, int & index, float x, float y, float z, float r, float g, float b, bool type);
protected:
	int count = 0;
	int dim = 0;
public:
	virtual float* generateVertieces(float* params);
	VertexGenerator();
	virtual ~VertexGenerator();
	int Size() { return size; }
	int QuadSize() { return quadSize; }
	int Count() { return count; }
	int Dim() { return dim; }
};

