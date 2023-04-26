#include "pch.h"
#include "VertexShader.h"


std::string VertexShader::Source()
{
	return
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec4 aCol;\n"
		"layout (location = 2) in float aKind;\n"
		"uniform mat4 modelRot;\n"
		"uniform mat4 modelRot2;\n"
		"uniform mat4 trans;\n"
		"uniform mat4 trans2;\n"
		"uniform mat4 proj;\n"
		"uniform mat4 view;\n"
		"uniform float wT;\n"
		"uniform float xRadius;\n"
		"uniform float yRadius;\n"
		"uniform float zRadius;\n"
		"out float xPos;\n"
		"out float yPos;\n"
		"out float zPos;\n"
		"out vec4 col;\n"
		"out float kind;\n"
		"void main()\n"
		"{\n"
		//"	float x=xRadius*cos(aPos.x)*sin(aPos.z);\n"					//SFERA
		//"	float z=zRadius*cos(aPos.x)*cos(aPos.z);\n"
		//"	float y=yRadius*sin(aPos.x);\n"
		//"	float x=xRadius*cos(aPos.x)*sin(2*aPos.z);\n"				//KLEPSYDRA
		//"	float z=zRadius*sin(aPos.x)*sin(2*aPos.z);\n"
		//"	float y=yRadius*sin(aPos.z);\n"
		"	float x=0.5*xRadius*sin(aPos.x)*sin(2*aPos.z);\n"			//MUSZLA
		"	float z=zRadius*cos(2*aPos.x)*sin(aPos.z)*sin(aPos.z);\n"
		"	float y=yRadius*sin(2*aPos.x)*sin(aPos.z)*sin(aPos.z);\n"
		"   gl_Position = (proj*view*trans2*modelRot*trans*modelRot2)*vec4(x, y, z, 1.0);\n"
		"	xPos=gl_Position.x;\n"
		"	yPos=gl_Position.y;\n"
		"	zPos=gl_Position.z;\n"
		"	if (aKind==0)\n"
		"		col=aCol;\n"
		"	else\n"
		"		col=vec4(1-aCol.r, 0.5f, 1-aCol.b, 1.0f);\n"
		"	kind=aKind;\n"
		"}\0";
}

VertexShader::VertexShader()
{
}


VertexShader::~VertexShader()
{
}
