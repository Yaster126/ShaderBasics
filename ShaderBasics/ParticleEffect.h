#pragma once
#include "Particle.h"
#include "VertexGenerator.h"
#include "Scene.h"
#include <vector>
template <typename P>
class ParticleEffect:public VertexGenerator, public AGPUProgram
{
private:
	std::vector<P> livingParticles;
public:

	ParticleEffect();
	~ParticleEffect();
	virtual float* generateVertieces(float* params) override;

	// Inherited via AGPUProgram
	virtual bool bindVertieces(VertexGenerator & vGen, float dT, float wT) override;

	void UpdateParticles(int count, int phaseCount, float radius, float cX, float cY, float cZ);
};

template<typename P>
inline ParticleEffect<P>::ParticleEffect()
{
		srand(time(NULL));
}

template<typename P>
inline ParticleEffect<P>::~ParticleEffect()
{

}

template<typename P>
inline float * ParticleEffect<P>::generateVertieces(float * params)
{

	float dT = params[0];
	this->count = livingParticles.size()*P::VertiecesPerParticle();
	this->dim = P::VertexDimentionality();
	
	float* vertices = new float[this->Count()*this->Dim()];
	int index = 0;
	for (auto lPart = livingParticles.begin(); lPart != livingParticles.end(); ++lPart)
		(*lPart)(vertices, index, dT);
	return vertices;
}

template<typename P>
bool ParticleEffect<P>::bindVertieces(VertexGenerator & vGen, float dT, float wT)
{
	GLuint VBO, VAO;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	float p[1] = {dT};
	float* vertices = generateVertieces(p);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	int size = livingParticles.size()*P::VertiecesPerParticle()*P::VertexDimentionality();
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
	//age attribute
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// position attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(sizeof(float)));
	glEnableVertexAttribArray(1);
	// color attribute
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//phase attribute
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
	//death time attribute
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(10 * sizeof(float)));
	glEnableVertexAttribArray(4);
	glUseProgram(shaderProgram);
	delete[] vertices;
	return true;
}

template<typename P>
inline void ParticleEffect<P>::UpdateParticles(int count, int phaseCount, float radius, float cX, float cY, float cZ)
{
	for (auto lPar = livingParticles.begin(); lPar != livingParticles.end(); )
	{
		if (lPar->isDeath())
			lPar = livingParticles.erase(lPar);
		else
			++lPar;
	}
	float ps = 6.28 / phaseCount;
	for (float t = 0; t <= 6.28; t += 6.28 / (float)count) 
	{
		for (float p = 0; p < phaseCount; p++) {
			float px = 3.14f*(float)(rand() % 1000 + 1) / 4000.0f;
			float py = 3.14f*(float)(rand() % 1000 + 1) / 4000.0f;
			float lt = 2;// (float)(rand() % 1000 + 1000) / 1000.0f;
			float x = cX + radius * cosf(t);
			float z = cZ + radius * sinf(t);
			livingParticles.push_back(P(lt, x, cY, z, p*ps+px, p*ps+py));
		}
	}
}

typedef ParticleEffect<Particle> OnePointParticleEffect;