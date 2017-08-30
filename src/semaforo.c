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
float RotX = 0.0, RotY = 0.0;
// controla se ativa a visualizacao do sistema de coordenadas
int verSistCoord = 0;

// Dimensiona a projecao
float nearV = 15;
float farV = 50;
float leftV = -10;
float rightV = 10;
float upperV = 10;
float bottomV = -10;

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
	glFrustum(leftV, rightV, bottomV, upperV, nearV, farV);
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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(13.0, 4.0, 20,       // foco F(13, 4, 20),
			  8.0, 4.0, 12.0,      // visada para (8, 4, 12)
			  0.0, 1.0, 0.0);      // e vert.V(0, 1, 0)
	// rotaciona
	glRotatef(RotX, 1.0, 0.0, 0.0);
	glRotatef(RotY, 0.0, 1.0, 0.0);

	// desenha sistema de coordenadas se ativo
	if (verSistCoord)
		sistCoord();

	// desenha semaforo
	semaforo();

	glutSwapBuffers();
	
}

// teclas padrao
void teclas(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'a':
		leftV+=0.1;
		rightV-=0.1;
		upperV-=0.1;
		bottomV+=0.1;
		break;
	case 's':
		leftV-=0.1;
		rightV+=0.1;
		upperV+=0.1;
		bottomV-=0.1;
		break;
		//...
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(leftV, rightV, bottomV, upperV, nearV, farV);
	glutPostRedisplay();
}

// Trata das teclas especiais
void teclas_especiais(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		upperV+=0.1;
		bottomV+=0.1;
		break;
	case GLUT_KEY_DOWN:
		upperV-=0.1;
		bottomV-=0.1;
		break;
	case GLUT_KEY_LEFT:
		leftV-=0.1;
		rightV-=0.1;
		break;
	case GLUT_KEY_RIGHT:
		leftV+=0.1;
		rightV+=0.1;
		break;
	case GLUT_KEY_HOME:
		++RotY;
		break;
	case GLUT_KEY_END:
		--RotY;
		break;
	case GLUT_KEY_PAGE_UP:
		--RotX;
		break;
	case GLUT_KEY_PAGE_DOWN:
		++RotX;
		break;
	case GLUT_KEY_F1:
		verSistCoord = 1 - verSistCoord;
		break;
	}

	printf("RotX = %.1f RotY = %.1f\n", RotX, RotY);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(leftV, rightV, bottomV, upperV, nearV, farV);
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
		
	puts("setas - move, pageup/pagedown - rotaciona(x), home/end -"
			" rotaciona(y),\n a/s - zoom, F1-mostra sist.coord., ESC-encerra");

	// prepara
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);

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
