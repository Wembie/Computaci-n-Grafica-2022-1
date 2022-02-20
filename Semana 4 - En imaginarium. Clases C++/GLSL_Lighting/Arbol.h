#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"

class Arbol
{
public:
	Arbol() {};
	void DibujarArbol(float posX, float posY, float posZ);
	~Arbol() {};
};
