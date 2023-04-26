#pragma once
#include "Scene.h"
#include "ParticleEffect.h"
#include "EnvelopedSpringVertShader.h"
#include "ParticleFragShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

template <class GProgram, class VGenerator>
class ParticleScene :
	public Scene<GProgram, VGenerator>
{
private:
	float sceneAngle = 45.0f;
	float modelAngle = 45.0f;
public:
	ParticleScene();
	~ParticleScene();
	


	// Inherited via Scene
	virtual void drawVertieces() override;

	virtual void addShaders() override;

	virtual void initializeScene() override;

	virtual void update() override;

};

template<class GProgram, class VGenerator>
inline ParticleScene<GProgram, VGenerator>::ParticleScene()
{
	

}

template<class GProgram, class VGenerator>
inline ParticleScene<GProgram, VGenerator>::~ParticleScene()
{
}

template<class GProgram, class VGenerator>
inline void ParticleScene<GProgram, VGenerator>::drawVertieces()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, this->program.Count());
}

template<class GProgram, class VGenerator>
inline void ParticleScene<GProgram, VGenerator>::addShaders()
{
	this->program.addShader(std::static_pointer_cast<AShader>(std::make_shared<EnvelopedSpringVertShader>()));
	this->program.addShader(std::static_pointer_cast<AShader>(std::make_shared<ParticleFragShader>()));
}

template<class GProgram, class VGenerator>
inline void ParticleScene<GProgram, VGenerator>::initializeScene()
{
	glm::mat4 modelRot = glm::mat4(1.0f);

	this->program.addMatrix4x4f(glm::perspective(30.0, 10.0 / 6.0, 0.1, 200.0), "proj");
	this->program.addMatrix4x4f(glm::lookAt(glm::vec3(0, 0.0f, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)), "view");
	this->program.addFloat(0.33, "amplitudeCos");
	this->program.addFloat(0.33, "amplitudeSin");
	this->program.addFloat(0.25, "expFrequencyCos");
	this->program.addFloat(0.25, "expFrequencySin");
	this->program.addFloat(3, "cosFrequency");
	this->program.addFloat(3.14, "cosPhase");
	this->program.addFloat(3, "sinFrequency");
	this->program.addFloat(3.14, "sinPhase");
}

template<class GProgram, class VGenerator>
inline void ParticleScene<GProgram, VGenerator>::update()
{
	this->program.bindVertieces(this->vGenerator, this->dT, this->wT);

	glm::mat4 modelRot = glm::mat4(1.0f);
	modelRot = glm::rotate(modelRot, glm::radians(modelAngle), glm::vec3(0.0, 1.0, 0.0));
	this->program.addMatrix4x4f(modelRot, "modelRot");

	glm::mat4 sceneRot = glm::mat4(1.0f);
	sceneRot = glm::rotate(sceneRot, glm::radians(sceneAngle), glm::vec3(0.0, 1.0, 0.0));
	this->program.addMatrix4x4f(sceneRot, "sceneRot");

	this->program.addFloat(1.0f, "wT");

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0, 0.0, 0));
	this->program.addMatrix4x4f(trans, "trans");

	sceneAngle += 30.0f*this->dT;
	modelAngle -= 90.0f*this->dT;

	this->program.UpdateParticles(1, 6, 0.05, 0, 2, 0);
}
