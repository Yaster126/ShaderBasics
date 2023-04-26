#pragma once
#include "Scene.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
template <class GProgram, class VGenerator>
class SphereScene :
	public Scene<GProgram,VGenerator>
{
private:
	float modelAngle = 45.0f;
	float xRadius = 1.0f;
	float rdx = 1.0f;
	float yRadius = 1.0f;
	float rdy = 1.0f;
	float zRadius = 1.0f;
	float rdz = 1.0f;
	
public:
	SphereScene();
	~SphereScene();

	// Inherited via Scene
	virtual void drawVertieces() override;
	virtual void addShaders() override;
	virtual void initializeScene() override;
	virtual void update() override;
};

template<class GProgram, class VGenerator>
inline SphereScene<GProgram, VGenerator>::SphereScene()
{
}

template<class GProgram, class VGenerator>
inline SphereScene<GProgram, VGenerator>::~SphereScene()
{
}

template<class GProgram, class VGenerator>
void SphereScene<GProgram, VGenerator>::drawVertieces()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int size = this->vGenerator.QuadSize()*this->vGenerator.Count();

	glDrawArrays(GL_TRIANGLES /*GL_QUADS*/, 0, this->vGenerator.QuadSize()*this->vGenerator.Count());
	glDrawArrays(GL_LINES, this->vGenerator.QuadSize()*this->vGenerator.Count(), (this->vGenerator.Size() - this->vGenerator.QuadSize())*this->vGenerator.Count());
}

template<class GProgram, class VGenerator>
inline void SphereScene<GProgram, VGenerator>::addShaders()
{
	this->program.addShader(std::static_pointer_cast<AShader>(std::make_shared<FragmentShader>()));
	this->program.addShader(std::static_pointer_cast<AShader>(std::make_shared<VertexShader>()));
}

template<class GProgram, class VGenerator>
inline void SphereScene<GProgram, VGenerator>::initializeScene()
{
	glm::mat4 modelRot = glm::mat4(1.0f);

	this->program.addMatrix4x4f(glm::perspective(30.0, 10.0 / 6.0, 0.1, 5.0), "proj");
	this->program.addMatrix4x4f(glm::lookAt(glm::vec3(0, -1.0f, -2.3f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)), "view");
	//program.addMatrix4x4f(glm::ortho(-4.0f, 4.0f,-4.0f, 4.0f, -4.0f, 4.0f), "proj");
	/*program.addMatrix4x4f(glm::mat4(1.0f), "view");*/
	this->program.addFloat(xRadius, "xRadius");
	this->program.addFloat(yRadius, "yRadius");
	this->program.addFloat(zRadius, "zRadius");
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
}

float test = 0.0f;
float dir = 1.0f;
float modelAngle2 = 45.0f;

template<class GProgram, class VGenerator>
inline void SphereScene<GProgram, VGenerator>::update()
{
	


	glm::mat4 modelRot = glm::mat4(1.0f);
	modelRot = glm::rotate(modelRot, glm::radians(modelAngle), glm::vec3(0.0, 1.0, 0.0));
	this->program.addMatrix4x4f(modelRot, "modelRot");

	glm::mat4 modelRot2 = glm::mat4(1.0f);
	//modelRot2 = glm::rotate(modelRot, glm::radians(modelAngle2), glm::vec3(0.0, 0.0, -1.0));
	this->program.addMatrix4x4f(modelRot2, "modelRot2");

	this->program.addFloat(1.0f, "wT");

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3( -1.5, glm::sin(test), 0.0));
	this->program.addMatrix4x4f(trans, "trans");
	
	glm::mat4 trans2 = glm::mat4(1.0f);
	//trans2 = glm::translate(trans, glm::vec3( -1.5, glm::sin(test), 0.0));
	this->program.addMatrix4x4f(trans2, "trans2");

	

	this->program.addFloat(xRadius, "xRadius");
	this->program.addFloat(yRadius, "yRadius");
	this->program.addFloat(zRadius, "zRadius");

	
	modelAngle -= 90.0f*this->dT;
	modelAngle2 -= 0.000001f;
	
	//xRadius -= rdx * 0.25f*this->dT;
	if (xRadius<0.5f || xRadius>1.0f)
		rdx = -1 * rdx;
	//yRadius -= rdy * 0.2f*this->dT;
	if (yRadius<0.5f || yRadius>1.0f)
		rdy = -1 * rdy;
	//zRadius -= rdz * 0.15f*this->dT;
	if (zRadius<0.2f || zRadius>1.0f)
		rdz = -1 * rdz;

	test += dir * 0.005f;
	if (test > 180.0f || test < -180.0f)
		dir *= -1;
}
