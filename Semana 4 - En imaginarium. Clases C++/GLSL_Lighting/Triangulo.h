#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"

class Triangulo
{
public:
	Triangulo() {};
	void DibujarTriangulo(float posX, float posY, float posZ);
	~Triangulo() {};
};
