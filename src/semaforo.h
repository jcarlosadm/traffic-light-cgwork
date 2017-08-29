#include <math.h>
#define M_PI 3.14159265358979323846

/*Lista de vertices:  */
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
/* Lista de poligonos:   */
GLint polig[][5] =
{
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
void Poligono(GLint *p)
{
    int i;
    glBegin(GL_LINE_LOOP);
    for(i=1; i<=p[0]; i++)
        glVertex3fv(vert[p[i]]);
    glEnd();
}

void circulo(GLfloat red, GLfloat green, GLfloat blue, GLfloat x, GLfloat y,
		GLfloat z, GLfloat radius) {

	glColor3f(red,green,blue);
	glBegin(GL_LINE_LOOP);
	int i;
	for(i=0;i<100;i++)
		glVertex3d(x + (radius * cos(i * 2.0 * M_PI / 100)),
				y + (radius * sin(i * 2.0 * M_PI / 100)),
				z - (radius * cos(i * 2.0 * M_PI / 100)));
	glEnd();
}

void semaforo(void)
{
    int i;
    glColor3f(1.0,1.0,0.5);      // todas as linhas em amarelo
    for(i=0; i<12; i++) Poligono(polig[i]);

    GLfloat x = 0.5, y = 4.0 + (4.0/6.0), z = 0.5, radius = 4.0/9.0;

    // semaforo verde
    circulo(0.0,1.0,0.0,x,y,z,radius);

    // semaforo amarelo
    circulo(1.0,1.0,0.0,x,y + (4.0/3.0),z,radius);

    // semaforo vermelho
    circulo(1.0,0.0,0.0,x,y + (8.0/3.0),z,radius);
}
void sistCoord(void)
{
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
