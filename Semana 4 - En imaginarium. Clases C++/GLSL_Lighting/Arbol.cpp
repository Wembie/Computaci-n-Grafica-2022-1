#include "Arbol.h"

void Arbol::DibujarArbol(float posX, float posY, float posZ) {
	glPushMatrix();
	glTranslatef(posX, posY, posZ);
		//tallo
		glPushMatrix();
			glRotated(90, 1, 0, 0);
			glutSolidCylinder(0.25, 1, 10, 5);
			
		glPopMatrix();
		//hojas
		glPushMatrix();
			glTranslatef(0.50, 0.5, 0);
			glutSolidSphere(0.5, 30,30);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0.5, 0);
			glutSolidSphere(0.5, 30, 30);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.50, 0.5, 0);
			glutSolidSphere(0.5, 30, 30);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.25, 1, 0);
			glutSolidSphere(0.5, 30, 30);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.25, 1, 0);
			glutSolidSphere(0.5, 30, 30);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 1.5, 0);
			glutSolidSphere(0.5, 30, 30);
		glPopMatrix();

	glPopMatrix();
}