#include "pch.h"
#include "EnvelopedSpringVertShader.h"


EnvelopedSpringVertShader::EnvelopedSpringVertShader()
{
}


EnvelopedSpringVertShader::~EnvelopedSpringVertShader()
{
}

std::string EnvelopedSpringVertShader::Source()
{ 
	return
		"#version 330 core\n"
		"layout (location = 0) in float time;\n"
		"layout (location = 1) in vec3 p;\n"
		"layout (location = 2) in vec4 c;\n"
		"layout (location = 3) in vec2 phase;\n"
		"layout (location = 4) in float deathTime;\n"
		"uniform float amplitudeCos;\n"
		"uniform float amplitudeSin;\n"
		"uniform float expFrequencyCos;\n"
		"uniform float expFrequencySin;\n"
		"uniform float cosFrequency;\n"
		"uniform float cosPhase;\n"
		"uniform float sinFrequency;\n"
		"uniform float sinPhase;\n"
		"uniform mat4 modelRot;\n"
		"uniform mat4 sceneRot;\n"
		"uniform mat4 trans;\n"
		"out vec4 col;\n"
		"varying float life;\n"
		"uniform mat4 proj;\n"
		"uniform mat4 view;\n"
		"float rand(vec2 co) {\n"
		"	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);\n"
		"}\n"
		"void main()\n"
		"{\n"
		"	float x, y, t, r,s;\n"
		"	r=rand(vec2(time, p.y));\n"
		"   t = (1-r*0.3)* (8 - time * 6.5);\n"
		"	s=1-0.3*rand(vec2(time, p.z));\n"
		"   x=amplitudeCos * exp(-t * t*expFrequencyCos)*cos(cosFrequency*t + phase.x*s);\n"
		"   y=amplitudeSin * exp(-t * t*expFrequencySin)*sin(sinFrequency*t + phase.y*s);\n"
		"   gl_Position = (proj*view*sceneRot)*vec4(p.x+x, p.y-time, p.z+y, 1.0);\n"
		"	col=c;\n"
		"	life=time/ deathTime;\n"
		"}\0";
}

