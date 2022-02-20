#include "Casa.h"

void Casa::DibujarCasa(float posX, float posY, float posZ) {
	glPushMatrix();

		glTranslatef(posX, posY, posZ);

		//Muros
		glutSolidCube(0.5);

		//Techo
		glPushMatrix();
			glTranslatef(0, 0.25, 0);
			glBegin(GL_TRIANGLES);
				glVertex3f(-0.5, 0, 0);
				glVertex3f(0.5, 0, 0);
				glVertex3f(0, 0.866, 0);
			glEnd();
		glPopMatrix();

	glPopMatrix();
}