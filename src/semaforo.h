#include <math.h>
#define M_PI 3.14159265358979323846

// variaveis de controle do semaforo
int redOn = 0;
int yellowOn = 0;
int greenOn = 0;

/*Lista de vertices ("pontos") dos poligonos:
 * cada vertice tem coordenadas x, y e z
 * */
GLfloat vert[][3]=
{
	// vertices do topo
    { 0.0, 4.0, -1.0},
    { 1.0, 4.0,  0.0},
    { 0.0, 4.0,  1.0},
    {-1.0, 4.0,  0.0},
    {-1.0,  8.0,  0.0},
    { 0.0,  8.0,  1.0},
    { 1.0,  8.0,  0.0},
    { 0.0,  8.0, -1.0},
	// vertices da haste
	{ 0.0, 4.0, -0.3},
	{ 0.3, 4.0,  0.0},
	{ 0.0, 4.0,  0.3},
	{-0.3, 4.0,  0.0},
	{-0.3, -8.0,  0.0},
	{ 0.0, -8.0,  0.3},
	{ 0.3, -8.0,  0.0},
	{ 0.0, -8.0, -0.3}
};

/* Lista de poligonos
 * o primeiro numero: a quantia de vertices do poligono (4 significa 4 vertices)
 * os outros numeros sao os vertices da lista de vertices
 * (por exemplo, 0 significa o vertice 0 da lista de vertices)
 * */
GLint polig[][5] =
{
	// topo
    {4, 0, 1, 2, 3},
    {4, 0, 7, 6, 1},
    {4, 1, 6, 5, 2},
    {4, 2, 5, 4, 3},
    {4, 3, 0, 7, 4},
    {4, 4, 5, 6, 7},
	// haste
	{4, 8, 9, 10, 11},
	{4, 8, 15, 14, 9},
	{4, 9, 14, 13, 10},
	{4, 10, 13, 12, 11},
	{4, 11, 8, 15, 12},
	{4, 12, 13, 14, 15},
};

/**
 * desenha cada poligono
 * recebe um array, que representa um elemento da lista de poligonos
 */
void Poligono(GLint *p)
{
    int i;
    // comeca a desenhar em linha em loop
    glBegin(GL_LINE_LOOP);
    // constroi o poligono pegando qual o vertice do array, e esse vertice da lista de vertices
    for(i=1; i<=p[0]; i++)
        glVertex3fv(vert[p[i]]);
    glEnd();
}

/**
 * desenha cada circulo com preenchimento
 * red, green, blue sao as cores
 * x, y, z: a posicao do circulo
 * radius: raio do circulo
 */
void circulo(GLfloat red, GLfloat green, GLfloat blue, GLfloat x, GLfloat y,
		GLfloat z, GLfloat radius) {

	// cor
	glColor3f(red,green,blue);
	// objeto com preenchimento
	glBegin(GL_TRIANGLE_FAN);
	int i;

	// desenha o circulo
	for(i=0;i<100;i++)
		glVertex3d(x + (radius * cos(i * 2.0 * M_PI / 100)) ,
				y + (radius * sin(i * 2.0 * M_PI / 100)),
				z - (radius * cos(i * 2.0 * M_PI / 100)));
	glEnd();
}

/**
 * desenha o semaforo
 */
void semaforo(void)
{
    int i;

    // todas as linhas em amarelo
    glColor3f(1.0,1.0,0.5);

    // desenha todos os poligonos da lista de poligonos
    for(i=0; i<12; i++)
    	Poligono(polig[i]);

    // posicoes padrao e raio dos circulos
    GLfloat x = 0.5, y = 4.0 + (4.0/6.0), z = 0.5, radius = 4.0/9.0;

    /**
     * cada circulo pode ter mais ou menos intensidade, a depender das variaveis
     * de controle greenOn, yellowOn e redOn
     */

    // circulo verde
    if (greenOn)
		circulo(0.0,1.0,0.0,x,y,z,radius);
	else 
		circulo(0.0,0.5,0.0,x,y,z,radius);

    // circulo amarelo
    if (yellowOn)
		circulo(1.0,1.0,0.0,x,y + (4.0/3.0),z,radius);
	else
		circulo(0.5,0.5,0.0,x,y + (4.0/3.0),z,radius);
    // circulo vermelho
    if (redOn)
		circulo(1.0,0.0,0.0,x,y + (8.0/3.0),z,radius);
	else 
		circulo(0.3,0.0,0.0,x,y + (8.0/3.0),z,radius);
}

/**
 * desenha o sistema de coordenadas
 */
void sistCoord(void)
{
	// comeca a desenhar cada linha
	// cada linha so precisa de dois vertices
    glBegin(GL_LINES);

    glColor3f(1.0, 0.0, 0.0);  // eixo x - vermelho
    glVertex3f(-3.0, 0.0, 0.0);
    glVertex3f(3.0,  0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0);  // eixo y - verde
    glVertex3f(0.0, -3.0, 0.0);
    glVertex3f(0.0,  3.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);  // eixo z - azul
    glVertex3f(0.0, 0.0, -3.0);
    glVertex3f(0.0, 0.0,  3.0);

    glEnd();
}
