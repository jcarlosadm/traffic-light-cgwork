//---------------------------------------------------------------------------
#ifdef _WIN32

#include <windows.h>
#include <gl\glut.h>

#else

#include <GL/glut.h>
#include <unistd.h>

#endif

#include <stdio.h>
//---------------------------------------------------------------------------
#include "semaforo.h"

float RotX = 0.0, RotY = 0.0;
int verSistCoord = 0;
// window dim
int nearV = -15;
int farV = 15;
int leftV = -10;
int rightV = 10;
int upperV = 10;
int bottomV = -10;
uint time;

//---------------------------------------------------------------------------
void dimensionaJanela(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(leftV, rightV, bottomV, upperV, nearV, farV);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	//limpa-buffers e outras inicializacoes;
}




void desenha() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(RotX, 1.0, 0.0, 0.0);
	glRotatef(RotY, 0.0, 1.0, 0.0);

	if (verSistCoord)
		sistCoord();

	semaforo();

	glPopMatrix();
	glutSwapBuffers();
	
}
void teclas(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
		//...
	}
}
// Trata das teclas especiais
void teclas_especiais(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		++RotX;
		break;
	case GLUT_KEY_DOWN:
		--RotX;
		break;
	case GLUT_KEY_RIGHT:
		++RotY;
		break;
	case GLUT_KEY_LEFT:
		--RotY;
		break;
	case GLUT_KEY_F1:
		verSistCoord = 1 - verSistCoord;
		break;
	}

	printf("RotX = %.1f RotY = %.1f\n", RotX, RotY);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(leftV, rightV, bottomV, upperV, nearV, farV);
	glutPostRedisplay();
}

void animation () {
	
		uint newTime = glutGet(GLUT_ELAPSED_TIME);
		if (newTime - time < 1000) return;
		time = newTime;
		
		if (redOn + yellowOn + greenOn == 0 || yellowOn == 1) {
			yellowOn = 0;
			redOn = 1;
		} else if (redOn == 1) {
			redOn = 0;
			greenOn = 1;
		} else if (greenOn == 1) {

		greenOn = 0;
		yellowOn = 1;
	}
	glutPostRedisplay();
	
}



int main(int argc, char *argv[]) {
		
	puts("setas-gira, F1-mostra sist.coord., ESC-encerra");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 600);

	glutCreateWindow("Semaforo");

	glutReshapeFunc(dimensionaJanela);
	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclas);
	glutSpecialFunc(teclas_especiais);
	time = glutGet(GLUT_ELAPSED_TIME);
	glutIdleFunc( animation );

	
	initGL();
	glutMainLoop();
	return (0);
}
