#include "Aleatorio.h"

void Aleatorio::DibujarAleatorio(float posX, float posY, float posZ) {
	glPushMatrix();
		glTranslatef(posX, posY, posZ);
		glRotatef(0.09 * 360, 0.5, 1.0f, 0.1f);
		glutSolidRhombicDodecahedron();
	glPopMatrix();
}