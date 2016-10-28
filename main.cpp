/* Replica del sistema solar. Autor: Guillermo Ramos Valverde */
// DISTANCIAS Y VELOCIDADES ANGULARES A ESCALA. TAMAÑOS FICTICIOS EN RELACIÓN A LAS DISTANCIAS INTERPLANETARIAS.

/* Cambios a realizar:
 * Suavizar trackball
 * Incluir satelites de los demás planetas
 * Incluir orbitas de satelites.
 * Añadir un menú
 * Añadir un fondo estrellado (skybox con cubemap)
 * Crear luz solar
 * Crear vistas para seguir a un planeta en concreto (nums 0-8)
*/

/*NOVEDADES:
 * CAMARA Y CONTROLES
 * Añadido pausa (click derecho) y eliminado velocidad contraria.
 * Añadido control de camara mediante trackball (click izquierdo).
 * Añadido zoom con rueda de ratón.
 * Mostrar/Ocultar órbitas en tecla F1
 * Control de velocidad en las flechas arriba y abajo.
 * Ajustes menores en el movimiento de camara.
 * SISTEMA SOLAR
 * Angulo de rotacion de la luna
 * Anillo de saturno
 */


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void destroyFunc();
void dibujarOrbitas();
void orbita(double planeta, double inclinacion, double giro);
void dibujarSol();
void dibujarPlaneta(double ang,GLfloat planeta_ambiente[],GLfloat planeta_difusa[],GLfloat planeta_especular[],double inclinacion, double distancia,double tamano);
void dibujarLuna(double angleMoon,double angleEarth);
void dibujarSaturno(double angleSaturn);
void dibujarCalisto();
void dibujarIo();
void dibujarGanimedes();
void dibujarEuropa();
void dibujarTitan();
void dibujarTriton();
void dibujarTitania();
void dibujarRea();
void dibujarObreron();
void funIdle();
void funKeyboard(int key, int x, int y);
void funMouse(int button, int state,int x, int y);
void funMotion(int x,int y);

//Distancias planetarias al Sol
const double earthSun = 4.0;
const double moonEarth = 0.1027;
const double marsSun = 6.09;
const double mercurySun = 1.55;
const double venusSun = 2.89;
const double jupiterSun = 20.81;
const double saturnSun = 38.2;
const double uranusSun = 76.92;
const double neptuneSun = 120.23;
//Tamaños planetarios
const double earth =0.05;
const double mercury =0.027;
const double venus =0.05;
const double mars =0.0265;
const double jupiter =0.5486;
const double saturn =0.457;
const double uranus =0.199;
const double neptune =0.1932;
//Inclinaciones orbitales
const double earthInc =0;
const double mercuryInc =7.0;
const double venusInc =3.39;
const double marsInc =1.85;
const double jupiterInc =1.31;
const double saturnInc =2.49;
const double uranusInc =0.77;
const double neptuneInc =1.77;


// Variables generales
bool pause=false;
int w = 1000;
int h = 600;
bool showOrbit = true;
double speed = 1.0;
double angleMercury = rand() % 181;
double angleVenus = rand() % 181;
double angleEarth = rand() % 181;
double angleMoon = rand() % 181;
double angleMars = rand() % 181;
double angleJupiter = rand() % 181;
double angleSaturn = rand() % 181;
double angleUranus = rand() % 181;
double angleNeptune = rand() % 181;

//Variables para la camara
double radiusCam = 10.0;
double angXCam = 0.0;
double angYCam = 75*(2*PI/360);
double zCam = sin(angYCam)*sin(angXCam)*radiusCam;
double xCam = sin(angYCam)*cos(angXCam)*radiusCam;
double yCam = cos(angYCam)*radiusCam;

//Variables para el Trackball
int shifty;
int shiftx;


//una posicion para luz
GLfloat posicion1[] = {0.0,0.0,0.0,1.0};


//Parámetros de la luz solar
GLfloat ambiente1[] = {0.0,0.0,0.0,0.0};
GLfloat difusa1[] = {1.0,1.0,0.9,1.0};
GLfloat especular1[] = {1.0,1.0,0.8,1.0};
//Parámetros de la luz 2
GLfloat ambiente2[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat difusa2[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat especular2[] = { 0.8, 0.8, 0.8, 1.0 };


//Material Sun
GLfloat sun_ambiente[] = { 1.0, 1.0, 0.3, 1.0 };
GLfloat sun_difusa[] = { 1.0, 1.0, 0.3, 1.0};
GLfloat sun_especular[] = { 1.0, 1.0, 0.3, 1.0 };
//Material Earth
GLfloat earth_ambiente[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat earth_difusa[] = { 0.3, 0.3, 0.7, 1.0};
GLfloat earth_especular[] = { 0.1, 0.1, 0.3, 1.0 };
//Material Moon
GLfloat moon_ambiente[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat moon_difusa[] = { 0.8, 0.8, 0.8, 1.0};
GLfloat moon_especular[] = { 0.3, 0.3, 0.3, 1.0 };
//Material Mercury
GLfloat mercury_ambiente[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat mercury_difusa[] = { 0.8, 0.5, 0.2, 1.0};
GLfloat mercury_especular[] = { 0.3, 0.15, 0.1, 1.0 };
//Material Venus
GLfloat venus_ambiente[] = { 0.0, 0.00, 0.0, 0.0 };
GLfloat venus_difusa[] = { 0.7, 0.1, 0.0, 1.0};
GLfloat venus_especular[] = { 0.3, 0.1, 0.1, 1.0 };
//Material Mars
GLfloat mars_ambiente[] = { 0.0, 0.00, 0.0, 0.0 };
GLfloat mars_difusa[] = { 0.9, 0.2, 0.0, 1.0};
GLfloat mars_especular[] = { 0.3, 0.1, 0.0, 1.0 };
//Material Jupiter
GLfloat jupiter_ambiente[] = { 0.0, 0.0, 0.00, 0.0 };
GLfloat jupiter_difusa[] = { 0.8, 0.3, 0.25, 1.0};
GLfloat jupiter_especular[] = { 0.3, 0.1, 0.09, 1.0 };
//Material Saturn
GLfloat saturn_ambiente[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat saturn_difusa[] = { 0.9, 0.5, 0.4, 1.0};
GLfloat saturn_especular[] = { 0.3, 0.1, 0.08, 1.0 };
//Material Anillo
GLfloat ring_ambiente[] = { 0.5, 0.4, 0.4 , 1.0 };
GLfloat ring_difusa[] = { 0.7, 0.5, 0.4, 0.1};
GLfloat ring_especular[] = { 0.0, 0.0, 0.00, 0.0 };
//Material Uranus
GLfloat uranus_ambiente[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat uranus_difusa[] = { 0.5, 0.5, 0.9, 0.0};
GLfloat uranus_especular[] = { 0.1, 0.1, 0.2, 1.0 };
//Material Neptune
GLfloat neptune_ambiente[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat neptune_difusa[] = { 0.2, 0.2, 0.7, 1.0};
GLfloat neptune_especular[] = { 0.1, 0.1, 0.18, 1.0 };


int main(int argc, char** argv) {
 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Sistema solar v1.2 - Guillermo Ramos");
 // Inicializamos GLEW
    glewInit();
 // Inicializaciones específicas
    initFunc();
 // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutIdleFunc(funIdle);
    glutSpecialFunc(funKeyboard);
    glutMouseFunc(funMouse);
    glutMotionFunc(funMotion);
 // Bucle principal
    glutMainLoop();
 // Destrucción de objetos
    destroyFunc();
    return(0);
}

void initFunc() {
    // Configuracion de etapas del cauce
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void destroyFunc() {
}

void funReshape(int wnew, int hnew) {
 // Configuración del Viewport
    glViewport(0, 0, wnew, hnew);
 // Captura de w y h
    w = wnew;
    h = hnew;
}

void funDisplay() {
 // Borramos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 // Para configurar la matriz matriz P
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 // Matriz de Proyección P (Cámara)
    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;
    GLfloat fovy = 50.0f, nplane = 0.1f, fplane = 600.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Matriz de Vista V (Cámara)
    gluLookAt(xCam,yCam,zCam, 0.0,0.0,0.0, 0.0,1.0,0.0);
    //iluminacion
    glLightfv(GL_LIGHT0, GL_POSITION, posicion1);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, especular1);
    // Dibujamos los objetos del sistema solar (M)
    if (showOrbit) {
        glDisable(GL_LIGHTING);
        dibujarOrbitas();
        glEnable(GL_LIGHTING);
    }
    dibujarSol();
    dibujarPlaneta(angleMercury,mercury_ambiente,mercury_difusa,mercury_especular,mercuryInc, mercurySun,mercury);
    dibujarPlaneta(angleVenus,venus_ambiente,venus_difusa,venus_especular,venusInc, venusSun,venus);
    dibujarPlaneta(angleEarth,earth_ambiente,earth_difusa,earth_especular,earthInc, earthSun,earth);
    dibujarLuna(angleMoon,angleEarth);
    dibujarPlaneta(angleMars,mars_ambiente,mars_difusa,mars_especular,marsInc, marsSun,mars);
    dibujarPlaneta(angleJupiter,jupiter_ambiente,jupiter_difusa,jupiter_especular,jupiterInc, jupiterSun,jupiter);
    dibujarSaturno(angleSaturn);
    dibujarPlaneta(angleUranus,uranus_ambiente,uranus_difusa,uranus_especular,uranusInc, uranusSun,uranus);
    dibujarPlaneta(angleNeptune,neptune_ambiente,neptune_difusa,neptune_especular,neptuneInc, neptuneSun,neptune);   
 // Intercambiamos los buffers
    glutSwapBuffers();

}

void dibujarOrbitas(){
    glPushMatrix();
    glColor3f(0.1f,0.1f,0.1f);
    orbita(mercurySun,7.0,0.0);
    orbita(venusSun,3.39,0.0);
    orbita(earthSun,0.0,0.0);
    orbita(marsSun,1.85,0.0);
    orbita(jupiterSun,1.31,0.0);
    orbita(saturnSun,2.49,0.0);
    orbita(uranusSun,0.77,0.0);
    orbita(neptuneSun,1.77,0.0);
    glPopMatrix();
}

void orbita(double planeta, double inclinacion, double giro){
    glPushMatrix();
    glRotated(inclinacion, 1.0,0.0,0.0);
    glBegin(GL_LINE_STRIP);
        for(float angul = 0.0; angul<2*PI; angul +=0.01){
            float x = (float) planeta*sin(angul+PI+giro);
            float y = (float) planeta*cos(angul+PI+giro); 
            glVertex3f(x,0,y);
        }
    glEnd();
    glPopMatrix();
}

void dibujarSol(){
    //Material
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    GLfloat emision[] = {0.8,0.8,0.0,1.0};
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION,emision);
    glTranslated(0.0,0.0,0.0);
    glutSolidSphere(0.7,50,50);
    glPopMatrix();
    GLfloat emision0[] = {0.0,0.0,0.0,1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION,emision0);
}

void dibujarPlaneta(double ang,GLfloat planeta_ambiente[],GLfloat planeta_difusa[],GLfloat planeta_especular[],double inclinacion, double distancia,double tamano){
    //Material
    glMaterialfv(GL_FRONT, GL_AMBIENT, planeta_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, planeta_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, planeta_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glPushMatrix();
    //inclinacion del plano orbital
    glRotated(inclinacion, 1.0,0.0,0.0);
    //giro alrededor del sol
    glRotated(ang, 0.0,1.0,0.0);
    //posicionamiento
    glTranslated(distancia,0.0,0.0);
    glutSolidSphere(tamano,50,50);
    glPopMatrix();
}

void dibujarLuna(double angM,double angE){
    //Material
    glMaterialfv(GL_FRONT, GL_AMBIENT, moon_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, moon_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glPushMatrix();
    //giro alrededor del sol
    glRotated(angE, 0.0,1.0,0.0);
    //giro en torno a la tierra
    glTranslated(earthSun,0.0,0.0);
    glRotated(5.14,0.0,0.0,1.0);  //ANGULO DE ROTACION ALREDEDOR DE LA TIERRA
    glRotated(-angM,0.0,1.0,0.0);
    glTranslated(-earthSun,0.0,0.0);
    //posicionamiento
    glTranslated(earthSun+moonEarth,0.0,0.0);
    glutSolidSphere(0.0125,50,50);
    glPopMatrix();
}

void dibujarSaturno(double ang){//Material
    glMaterialfv(GL_FRONT, GL_AMBIENT, saturn_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, saturn_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, saturn_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glPushMatrix();
    //inclinacion del plano orbital
    glRotated(2.49, 1.0,0.0,0.0);
    //giro alrededor del sol
    glRotated(ang, 0.0,1.0,0.0);
    //posicionamiento
    glTranslated(saturnSun,0.0,0.0);
    glutSolidSphere(0.457,50,50);
    glRotated(70.0,1.0,0.0,0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ring_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ring_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ring_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 1);
    gluDisk(gluNewQuadric(), 0.63, 0.89, 50, 1);
    gluDisk(gluNewQuadric(), 0.93, 1.03, 50, 1);
    glPopMatrix();
}

void funIdle(){
    if (!pause){
        angleMercury = angleMercury+2.073*speed;
        angleVenus = angleVenus+0.81*speed;
        angleEarth = angleEarth+0.5*speed;
        angleMoon = angleMoon+6.76*speed;
        angleMars = angleMars+0.265*speed;
        angleJupiter = angleJupiter+0.0426*speed;
        angleSaturn = angleSaturn+0.01697*speed;
        angleUranus = angleUranus+0.00595*speed;
        angleNeptune = angleNeptune+0.003030*speed;
    }
    glutPostRedisplay();
}

void funKeyboard(int key, int x, int y){
     switch(key) {
         case GLUT_KEY_UP:
            if (speed < 10.0){
                speed = speed + 0.5;
            }
            break;
        case GLUT_KEY_DOWN:
            if (speed > 1){
                speed = speed - 0.5;
            }
            break;
        case GLUT_KEY_F1:
            showOrbit=!showOrbit;
            break;            
     }

    glutPostRedisplay();
}

void funMouse(int button, int state,int x, int y){
    switch (button){
        case 3:
            if (radiusCam>=2)
            radiusCam-=0.4;
            break;
        case 4:
            if (radiusCam<=170)
            radiusCam+=0.4;
            break;
        case GLUT_LEFT_BUTTON:
            if (state==GLUT_DOWN){
                shifty=y;
                shiftx=x;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state==GLUT_DOWN){
                pause=!pause;
            }
            break;            
    }
    zCam = sin(angYCam)*sin(angXCam)*radiusCam;
    xCam = sin(angYCam)*cos(angXCam)*radiusCam;
    yCam = cos(angYCam)*radiusCam;
}
void funMotion(int x,int y){
    if ((y > shifty)&&(x>shiftx)){
        if ((angYCam/(2*PI/360)>1)){            
            angYCam -= (y-shifty)*(PI/360);
        }
        angXCam += (x-shiftx)*(PI/360);  
    } else if ((y > shifty)&&(x<shiftx)){
        if ((angYCam/(2*PI/360)>1)){
            angYCam -= (y-shifty)*(PI/360);
        }
        angXCam -= (shiftx-x)*(PI/360);
    } else if ((y < shifty)&&(x>shiftx)){
        if ((angYCam/(2*PI/360)<179)){
            angYCam += (shifty-y)*(PI/360);
        }
        angXCam += (x-shiftx)*(PI/360);
    } else if ((y < shifty)&&(x<shiftx)){
        if ((angYCam/(2*PI/360)<179)){
            angYCam += (shifty-y)*(PI/360);
        }
        angXCam -= (shiftx-x)*(PI/360);
    }
    shiftx=x;
    shifty=y;
    zCam = sin(angYCam)*sin(angXCam)*radiusCam;
    xCam = sin(angYCam)*cos(angXCam)*radiusCam;
    yCam = cos(angYCam)*radiusCam;
}