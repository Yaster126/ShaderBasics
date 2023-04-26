#include "pch.h"
#include "AGPUProgram.h"
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
bool AGPUProgram::programLinkStatus()
{
	{
		GLint status;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint length;
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> log(length);
			glGetProgramInfoLog(shaderProgram, length, &length, &log[0]);
			std::cout << &log[0];
			return false;
		}
		std::cout << "Shaders linked to the program succesfully :-)";
		return true;
	}
}

AGPUProgram::AGPUProgram()
{
	
}

bool AGPUProgram::addShader(std::shared_ptr<AShader> shader)
{
	shader->initialize();
	if (!shader->Compile())
		return false;
	shaders.push_back(shader);
	return true;
}

bool AGPUProgram::linkShaders()
{
	shaderProgram = glCreateProgram();
	for (auto shader = shaders.begin(); shader != shaders.end(); ++shader) {
		glAttachShader(shaderProgram, (*shader)->ShaderGLObj());
	}
	glLinkProgram(shaderProgram);
	return programLinkStatus();
	
}

//bool AGPUProgram::bindVertieces(VertexGenerator& vGen)
//{
//	GLuint VBO, VAO;
//	//std::cout << "i=" << i << " sizeof="<< sizeof(vertices)<<";\n";
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//	glBindVertexArray(VAO);
//
//
//	//float* vertices = vGen.generateVertieces(-3.14f, 3.14f, 0.0314f, -1.57f, 1.57f, 0.0157f);
//	float p[6] = { -3.14f, 3.14f, 0.0314f, -3.14f, 3.14f, 0.0314f };
//	float* vertices = vGen.generateVertieces(p);
//	std::cout << "size=" << vGen.Size() << "\n";
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, vGen.Size()*vGen.Count()*vGen.Dim() * sizeof(float), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	glUseProgram(shaderProgram);
//	delete[] vertices;
//	return true;
//}


void AGPUProgram::addMatrix4x4f(glm::mat4 matrix, const GLchar* varName)
{
	GLuint loc = glGetUniformLocation(shaderProgram,varName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void AGPUProgram::addFloat(GLfloat f, const GLchar * varName)
{
	GLuint loc = glGetUniformLocation(shaderProgram, varName);
	glUniform1f(loc, f);
}

AGPUProgram::~AGPUProgram()
{
}






