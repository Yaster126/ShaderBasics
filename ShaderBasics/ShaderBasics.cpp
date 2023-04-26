#include "pch.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include "SphereScene.h"
#include "ParticleScene.h"
#include "ParticleEffect.h"
SphereScene<SphereGPUProgram, VertexGenerator> sphereScene;
ParticleScene<OnePointParticleEffect, OnePointParticleEffect> particleScene;
int chosenProgram = 0;
void display() {
	if (chosenProgram == 1)
		sphereScene.frame();
	else
		particleScene.frame();
}
int main(int argc, char **argv)
{
	std::cout << "[0]-run Particles\n[1]-run Sphere\nYour choice?: ";
	std::cin >> chosenProgram;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);
	
	glutCreateWindow("GK: Fragment and vertex shaders");
	glutReshapeWindow(1000, 600);
	glutDisplayFunc(display);
	if (chosenProgram == 1)
		sphereScene.init();
	else
		particleScene.init();
	glutMainLoop();
	return 0;
}
