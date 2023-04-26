#pragma once
#include "AShader.h"
class EnvelopedSpringVertShader :
	public AShader
{
public:
	EnvelopedSpringVertShader();
	
	~EnvelopedSpringVertShader();

	// Inherited via AShader
	virtual std::string Source() override;
	virtual int Type() override {
		return GL_VERTEX_SHADER;
	};
};

