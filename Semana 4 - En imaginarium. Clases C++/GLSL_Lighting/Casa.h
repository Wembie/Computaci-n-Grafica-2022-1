#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"

class Casa
{
	public:
		Casa() {};
		void DibujarCasa(float posX, float posY, float posZ);
		~Casa() {};
};

