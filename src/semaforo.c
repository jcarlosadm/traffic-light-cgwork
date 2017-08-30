//---------------------------------------------------------------------------

#ifdef _WIN32

// WINDOWS
#include <windows.h>
#include <gl\glut.h>

#else

// LINUX
#include <GL/glut.h>
#include <unistd.h>

#endif

#include <stdio.h>
//---------------------------------------------------------------------------
#include "semaforo.h"

// variaveis de controle de rotacao
float RotX = 0.0, RotY = 0.0, RotZ = 0.0;
// controla se ativa a visualizacao do sistema de coordenadas
int verSistCoord = 0;

// Dimensiona a projecao
int nearV = -15;
int farV = 15;
int leftV = -10;
int rightV = 10;
int upperV = 10;
int bottomV = -10;

// temporizador no semaforo
unsigned int time;

//---------------------------------------------------------------------------

/**
 * dimensiona janela
 */
void dimensionaJanela(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(leftV, rightV, bottomV, upperV, nearV, farV);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * limpa-buffers e outras inicializacoes;
 */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
}

/**
 * desenha semaforo
 */
void desenha() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	// rotaciona
	glRotatef(RotX, 1.0, 0.0, 0.0);
	glRotatef(RotY, 0.0, 1.0, 0.0);
	glRotatef(RotZ, 0.0, 0.0, 1.0);

	// desenha sistema de coordenadas se ativo
	if (verSistCoord)
		sistCoord();

	// desenha semaforo
	semaforo();

	glPopMatrix();
	glutSwapBuffers();
	
}

// teclas padrao
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
	case GLUT_KEY_PAGE_UP:
		--RotZ;
		break;
	case GLUT_KEY_PAGE_DOWN:
		++RotZ;
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

/**
 * animacao
 */
void animation () {
	
	// pega o tempo atual
	unsigned int newTime = glutGet(GLUT_ELAPSED_TIME);

	if (newTime - time < 1000)
		return;

	// atualiza tempo
	time = newTime;

	// alterna entre os circulos do semaforo
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
		
	puts("setas - gira (eixo x/y), pageup/pagedown - gira (eixo z), F1-mostra sist.coord., ESC-encerra");

	// prepara
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 600);

	glutCreateWindow("Semaforo");

	// seta as funcoes
	glutReshapeFunc(dimensionaJanela);
	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclas);
	glutSpecialFunc(teclas_especiais);
	// pega tempo atual
	time = glutGet(GLUT_ELAPSED_TIME);

	// chama a funcao animation quando o glut nao ta tratando os eventos
	glutIdleFunc( animation );

	// inicia tudo
	initGL();
	glutMainLoop();

	return (0);
}
