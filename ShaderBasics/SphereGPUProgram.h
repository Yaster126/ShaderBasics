#pragma once
#include "AGPUProgram.h"

class SphereGPUProgram :
	public AGPUProgram
{
public:
	SphereGPUProgram();
	~SphereGPUProgram();

	// Inherited via AGPUProgram
	virtual bool bindVertieces(VertexGenerator & vGen, float dT, float wT) override;
};

