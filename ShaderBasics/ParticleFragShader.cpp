#include "pch.h"
#include "ParticleFragShader.h"


ParticleFragShader::ParticleFragShader()
{
}


ParticleFragShader::~ParticleFragShader()
{
}

std::string ParticleFragShader::Source()
{
	return
		"#version 330 core\n"
		"varying float life;\n"
		"out vec4 FragColor;\n"
		/*"layout(location = 0) out vec4 dColor;\n"
		"layout(location = 2) out vec4 sColor;\n"*/
		"void main()\n"
		"{\n"
		"		float x=life;\n"
		"		float r=sin(1.57*x);\n"
		"		float g=(sin(1.57*x)+cos(1.57*x))/2;\n"
		"		float b=cos(1.57*x);\n"
		"		FragColor=vec4(r, g,b,1);\n" //(0)
		//"		gl_FragColor=vec4(r, g,b,1);\n" //(1)
		/*"		dColor=vec4(r, g,b,1);\n"       //(2)
		"		sColor=vec4(r, g,b,1);\n"*/
		"}\0";

	/*
	UWAGA, dodatek, którego nie ma w nagraniach. 
	Powyżej są trzy możliwości ustawienia koloru fragmentu:
	(0)	poprzez zdefiniowanie własnej zmiennej wyjściowej, która musi być 
		czterowymiarowym wektorem floatów (vec4) reprezentującym kolor,
	(1)	poprzez użycie zmiennej wbudowanej gl_FragColor będącej wektorem 
		jak wyżej,
	(2)	poprzez użycie predefiniowanego bufora wyjściowego, czyli słowa layout.
		Pod indeksem 0 jest składowa Diffuse koloru, pod indeksem 2 składowa Specular.
		Więcej na temat modeli kolorów (np. czym są te składowe) będzie na zajęciach 
		z oświetlenia. Można również samodzielnie definiować layouty wyjściowe. 
		Jeśli ktoś jest zainteresowany, odsyłam do dokumentacji:
		https://www.khronos.org/opengl/wiki/Fragment_Shader
	*/
}

int ParticleFragShader::Type()
{
	return GL_FRAGMENT_SHADER;
}
