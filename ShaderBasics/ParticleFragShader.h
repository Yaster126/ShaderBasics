#pragma once
#include "AShader.h"
class ParticleFragShader :
	public AShader
{
public:
	ParticleFragShader();
	~ParticleFragShader();

	// Inherited via AShader
	virtual std::string Source() override;
	virtual int Type() override;
};

