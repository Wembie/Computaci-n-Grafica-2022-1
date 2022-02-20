#include "Tetera.h"

void Tetera::DibujarTetera(float posX, float posY, float posZ) {

	glPushMatrix();
	//glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);
		glTranslatef(posX, posY, posZ);
		glutSolidTeapot(0.5);
	glPopMatrix();
}