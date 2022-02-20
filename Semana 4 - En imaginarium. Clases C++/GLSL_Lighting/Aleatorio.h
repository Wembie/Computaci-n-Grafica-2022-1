#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"

class Aleatorio
{
public:
	Aleatorio() {};
	void DibujarAleatorio(float posX, float posY, float posZ);
	~Aleatorio() {};
};