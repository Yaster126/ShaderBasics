#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "AShader.h"
#include "VertexGenerator.h"
class AGPUProgram
{
private:
	std::vector< std::shared_ptr<AShader>> shaders;
	bool programLinkStatus();
protected:
	GLuint shaderProgram;
	
public:
	AGPUProgram();
	bool addShader(std::shared_ptr<AShader> shader);
	bool linkShaders();
	virtual bool bindVertieces(VertexGenerator& vGen, float dT, float wT)=0;
	GLuint ShaderProgram() { return shaderProgram; }
	void addMatrix4x4f(glm::mat4 matrix, const GLchar* varName);
	void addFloat(GLfloat, const GLchar* varName);
	~AGPUProgram();
};

