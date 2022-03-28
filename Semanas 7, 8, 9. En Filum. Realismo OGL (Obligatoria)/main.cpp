//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include <cstring>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include <FreeImage.h> //*** Para Textura: Incluir librer�a

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
	cwc::glShaderManager SM;
	cwc::glShader* shader;
	cwc::glShader* shader1; //Para Textura: variable para abrir los shader de textura
	GLuint ProgramObject;
	clock_t time0, time1;
	float timer010;  // timer counting 0->1->0
	bool bUp;        // flag if counting up or down.
	int numMallas = 11;
	std::string refObject[11] =
	{
		"buddha","candelabro","casa","gorila",
		"laberinto","Mazo","piramide","piramideAbstracta",
		"tower","trampaOsos","vigilante"
	};
   GLMmodel* objmodel_ptr[11];
   GLMmodel* objmodel_ptr1; //*** Para Textura: variable para objeto texturizado
   GLuint texid; //*** Para Textura: variable que almacena el identificador de textura
   bool xIzquierda, xDerecha, zFrente, zAtras;
   float posX, posZ;
   


public:
	myWindow(){}

	void moverMalla() {
		if (xIzquierda) {
			posX -= 0.05;
		}
		if (xDerecha) {
			posX += 0.05;
		}
		if (zFrente) {
			posZ += 0.05;
		}
		if (zAtras) {
			posZ -= 0.05;
		}
	}

	//*** Para Textura: aqui adiciono un m�todo que abre la textura en JPG
	void initialize_textures(void)
	{
		int w, h;
		GLubyte* data = 0;
		//data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
		//std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;

		//dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Loading JPG file
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType("./Mallas/WOOD20L.jpg", 0),
			"./Mallas/WOOD20L.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

		FreeImage_Unload(pImage);
		//
		glEnable(GL_TEXTURE_2D);
	}


	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!

      glPushMatrix();
	 // glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);
	  moverMalla();

      if (shader) shader->begin();
			//alejamos la camara en z para ver todo el panorama	
		 glTranslatef(0, 0, -3.1);
		 
		 // colocamos la casa 
		 glPushMatrix();
		 glScalef(0.5, 0.5, 0.5);
		 glTranslatef(0, -1, 0);
		  glmDraw(objmodel_ptr[2], GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  // colocamos a winston vigilante
		  glPushMatrix();
		  glScalef(0.2, 0.2, 0.2);
		  glTranslatef(posX,0, posZ);
		  glmDraw(objmodel_ptr[10], GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();

		  //colocamos el minindantia Tower
		  glPushMatrix();
		  glTranslatef(2.5, 0.1, 0);
		  glScalef(1.3, 1.3, 1.3);
		  glmDraw(objmodel_ptr[8], GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  //colocamos el minipax piramide
		  glPushMatrix();
		  glTranslatef(-2.5, 0, 0);
		  glmDraw(objmodel_ptr[6], GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  //colocamos el minimor piramideAbstracta
		  glPushMatrix();
		  glTranslatef(0, 0, -6);
		  glScalef(5, 5, 5);
		  glmDraw(objmodel_ptr[7], GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  
		  // Colocamos el laberinto
		  glPushMatrix();
		  glTranslatef(0, 0, -4);
		  glmDraw(objmodel_ptr[4], GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  // Colocamos los guardias
		  glPushMatrix();
		  glTranslatef(0.5, 0, -2.5);
		  glRotatef(180, 0, 1, 0);
		  glScalef(0.3, 0.3, 0.3);
		  glmDraw(objmodel_ptr[3], GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  glPushMatrix();
		  glTranslatef(-0.5, 0, -2.5);
		  glRotatef(180, 0, 1, 0);
		  glScalef(0.3, 0.3, 0.3);
		  glmDraw(objmodel_ptr[3], GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  
		  //colocamos el justicia piramideAbstracta de momento, cambiar
		  glPushMatrix();
		  glTranslatef(0, 0, 4);
		  glScalef(4, 4, 4);
		  glmDraw(objmodel_ptr[7], GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  


      if (shader) shader->end();
	  /*
	  //*** Para Textura: llamado al shader para objetos texturizados
	  if (shader1) shader1->begin();

		  glPushMatrix();
		  glTranslatef(1.5f, 0.0f, 0.0f);
		  glBindTexture(GL_TEXTURE_2D, texid);
		  glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		  glPopMatrix();
	  //glutSolidTeapot(1.0);
	  if (shader1) shader1->end();
	  */

      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
		if (shader == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shader->GetProgramObject();
		}
		/*
		//*** Para Textura: abre los shaders para texturas
		shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader1 == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shader1->GetProgramObject();
		}
		*/
		time0 = clock();
		timer010 = 0.0f;
		bUp = true;
		posX = 0.0;
		posZ = 0.0;

		//Abrir mallas
		
		for (int i = 0; i < numMallas;i++)
		{
			objmodel_ptr[i] = NULL;

			if (!objmodel_ptr[i])
			{
				std::string aux;
				aux = "./Mallas/" + refObject[i] + ".obj";
				char aux2[50];
				std::strcpy(aux2, aux.c_str());
				printf(aux2 );
				printf("\n");
				objmodel_ptr[i] = glmReadOBJ(aux2);
				if (!objmodel_ptr[i])
					exit(0);
				glmUnitize(objmodel_ptr[i]);
				glmFacetNormals(objmodel_ptr[i]);
				glmVertexNormals(objmodel_ptr[i], 90.0);
			}

		}	  


	  //*** Para Textura: abrir malla de objeto a texturizar
	  /*
		objmodel_ptr1 = NULL;

	  if (!objmodel_ptr1)
	  {
		  std::string aux;
		  aux = "./Mallas/" + refObject[0] + ".obj";
		  char aux2[50];
		  std::strcpy(aux2, aux.c_str());
		  objmodel_ptr1 = glmReadOBJ(aux2);
		  if (!objmodel_ptr1)
			  exit(0);

		  glmUnitize(objmodel_ptr1);
		  glmFacetNormals(objmodel_ptr1);
		  glmVertexNormals(objmodel_ptr1, 90.0);
	  }
	  */
	
	  //** Para Textura: abrir archivo de textura
	  //initialize_textures();
      
	  DemoLight();
	  
	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(60,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,8.0f,-15.0f, 
		          0.0,-1.0,.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 
		switch (cAscii){
			case('d'):
				xIzquierda = true;
				break;
			case('a'):
				xDerecha = true;
				break;
			case('w'):
				zFrente = true;
				break;
			case('s'):
				zAtras = true;
				break;
			default:
				break;
		}
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
		switch (cAscii) {
		case('d'):
			xIzquierda = false;
			break;
		case('a'):
			xDerecha = false;
			break;
		case('w'):
			zFrente = false;
			break;
		case('s'):
			zAtras = false;
			break;
		default:
			break;
		}
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     /*
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     */
     // ------------------------------------------- 
     // Lighting parameters:
	 /*
     GLfloat light_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
     GLfloat light_Ka[]  = {0.0f, 0.0f, 0.0f, 1.0f};
     GLfloat light_Kd[]  = {0.0f, 0.0f, 0.0f, 1.0f};
     GLfloat light_Ks[]  = {0.0f, 0.0f, 0.0f, 1.0f};

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
	 */	
     // -------------------------------------------
     // Material parameters:
	/*
     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
   
   */
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

