#pragma once
#include <gl/glew.h>

#include <ctime>
#include <chrono>
#include "FragmentShader.h"
#include "VertexShader.h"
#include "SphereGPUProgram.h"
template <class GProgram, class VGenerator>
class Scene
{
private:
	std::chrono::system_clock::time_point t;
	std::chrono::system_clock::time_point tBegin;
	bool first = true;
	void updateTimers();
	void updateGLState();
protected:
	float dT;
	float wT;
	GProgram program;
	VGenerator vGenerator;
	virtual void drawVertieces() = 0;
	virtual void addShaders() = 0;
	virtual void initializeScene() = 0;
	virtual void update() = 0;
public:
	void init();
	void frame(void);

	Scene();
	~Scene();
};

template <class GProgram, class VGenerator>
void Scene<GProgram, VGenerator>::updateTimers()
{
	std::chrono::system_clock::time_point tCurr = std::chrono::system_clock::now();

	if (first)
	{
		t = tCurr;
		tBegin = tCurr;
		first = false;
		return;
	}
	wT = (float)std::chrono::duration_cast<std::chrono::microseconds>(tCurr - tBegin).count() / 1000000;
	dT = (float)std::chrono::duration_cast<std::chrono::microseconds>(tCurr - t).count() / 1000000;
	t = tCurr;
}

template <class GProgram, class VGenerator>
void Scene<GProgram, VGenerator>::updateGLState()
{
	glutSwapBuffers();
	glutPostRedisplay();
}

template <class GProgram, class VGenerator>
void Scene<GProgram, VGenerator>::init()
{
	GLenum err = glewInit();
	addShaders();
	program.linkShaders();
	program.bindVertieces(vGenerator, dT, wT);
	initializeScene();
}

template <class GProgram, class VGenerator>
void Scene<GProgram, VGenerator>::frame(void)
{
	updateTimers();
	update();
	drawVertieces();
	updateGLState();
}

template <class GProgram, class VGenerator>
Scene<GProgram, VGenerator>::Scene()
{
}

template <class GProgram, class VGenerator>
Scene<GProgram, VGenerator>::~Scene()
{
}