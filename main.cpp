/* Replica del sistema solar. Autor: Guillermo Ramos Valverde */
// DISTANCIAS Y VELOCIDADES ANGULARES A ESCALA. TAMAÑOS FICTICIOS EN RELACIÓN A LAS DISTANCIAS INTERPLANETARIAS.

/* Cambios a realizar: 
 * Incluir anillo de saturno
 * Incluir satelites de los demás planetas
 * Añadir un menú
 * Añadir un fondo estrellado
 * Crear luz solar
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
void dibujarMercurio(double angleMercury);
void dibujarVenus(double angleVenus);
void dibujarTierra(double angleEarth);
void dibujarLuna(double angleMoon,double angleEarth);
void dibujarMarte(double angleMars);
void dibujarJupiter(double angleJupiter);
void dibujarSaturno(double angleSaturn);
void dibujarUrano(double angleUranus);
void dibujarNeptuno(double angleNeptune);
void funIdle();
void funKeyboard(unsigned char key, int x, int y);

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


/*AQUI PODRIAMOS INCLUIR TAMAÑOS PLANETARIOS COMO VARIABLES
 * 
 * 
 *
 * 
 */


// Variables generales 
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

//una posicion para luz 
GLfloat posicion1[] = {0.0,0.0,0.0,1.0};


//Parámetros de la luz solar
GLfloat ambiente1[] = {0.1,0.1,0.1,1.0};
GLfloat difusa1[] = {1.0,1.0,0.9,1.0};
GLfloat especular1[] = {1.0,1.0,0.8,1.0};
//Parámetros de la luz 2
GLfloat ambiente2[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat difusa2[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat especular2[] = { 0.8, 0.8, 0.8, 1.0 };


//Material Sun
GLfloat sun_ambiente[] = { 1.0, 1.0, 0.3, 1.0 };
GLfloat sun_difusa[] = { 1.0, 1.0, 0.3, 1.0};
GLfloat sun_especular[] = { 1.0, 1.0, 0.3, 1.0 };
//Material Earth
GLfloat earth_ambiente[] = { 0.0, 0.0, 0.1, 1.0 };
GLfloat earth_difusa[] = { 0.3, 0.3, 0.7, 1.0};
GLfloat earth_especular[] = { 0.1, 0.1, 0.3, 1.0 };
//Material Moon
GLfloat moon_ambiente[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat moon_difusa[] = { 0.8, 0.8, 0.8, 1.0};
GLfloat moon_especular[] = { 0.3, 0.3, 0.3, 1.0 };
//Material Mercury
GLfloat mercury_ambiente[] = { 0.2, 0.15, 0.1, 1.0 };
GLfloat mercury_difusa[] = { 0.8, 0.5, 0.2, 1.0};
GLfloat mercury_especular[] = { 0.3, 0.15, 0.1, 1.0 };
//Material Venus
GLfloat venus_ambiente[] = { 0.2, 0.05, 0.0, 1.0 };
GLfloat venus_difusa[] = { 0.7, 0.1, 0.0, 1.0};
GLfloat venus_especular[] = { 0.3, 0.1, 0.1, 1.0 };
//Material Mars
GLfloat mars_ambiente[] = { 0.2, 0.05, 0.0, 1.0 };
GLfloat mars_difusa[] = { 0.9, 0.2, 0.0, 1.0};
GLfloat mars_especular[] = { 0.3, 0.1, 0.0, 1.0 };
//Material Jupiter
GLfloat jupiter_ambiente[] = { 0.2, 0.1, 0.05, 1.0 };
GLfloat jupiter_difusa[] = { 0.8, 0.3, 0.25, 1.0};
GLfloat jupiter_especular[] = { 0.3, 0.1, 0.09, 1.0 };
//Material Saturn
GLfloat saturn_ambiente[] = { 0.2, 0.1, 0.05, 1.0 };
GLfloat saturn_difusa[] = { 0.9, 0.5, 0.4, 1.0};
GLfloat saturn_especular[] = { 0.3, 0.1, 0.08, 1.0 };
//Material Uranus
GLfloat uranus_ambiente[] = { 0.05, 0.05, 0.1, 1.0 };
GLfloat uranus_difusa[] = { 0.5, 0.5, 0.9, 1.0};
GLfloat uranus_especular[] = { 0.1, 0.1, 0.2, 1.0 };
//Material Neptune
GLfloat neptune_ambiente[] = { 0.1, 0.1, 0.2, 1.0 };
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
    glutKeyboardFunc(funKeyboard);
      
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
    dibujarMercurio(angleMercury);
    dibujarVenus(angleVenus);
    dibujarTierra(angleEarth);
    dibujarLuna(angleMoon,angleEarth);
    dibujarMarte(angleMars);
    dibujarJupiter(angleJupiter);
    dibujarSaturno(angleSaturn);
    dibujarUrano(angleUranus);
    dibujarNeptuno(angleNeptune);
    
    
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
    glBegin(GL_LINE_STRIP);
        for(float angul = 0.0; angul<2*PI; angul +=0.01){
            float x = (float) ((float) planeta*sin(angul+PI+giro));
            float y = (float) ((float) planeta*cos(angul+PI+giro)); 
            glVertex3f(x,cos(angul)*(((inclinacion*2*PI)/360)/asin(1/planeta)),y);
        }
    glEnd();
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

void dibujarMercurio(double ang){
    //Material 
    glMaterialfv(GL_FRONT, GL_AMBIENT, mercury_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mercury_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mercury_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glPushMatrix();    
    //inclinacion del plano orbital
    glRotated(7.0, 1.0,0.0,0.0);    
    //giro alrededor del sol
    glRotated(ang, 0.0,1.0,0.0);    
    //posicionamiento
    glTranslated(mercurySun,0.0,0.0);    
    glutSolidSphere(0.027,50,50); 
    glPopMatrix();
}

void dibujarVenus(double ang){
    //Material 
    glMaterialfv(GL_FRONT, GL_AMBIENT, venus_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, venus_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, venus_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 200);
    glPushMatrix();
    //inclinacion del plano orbital
    glRotated(3.39, 1.0,0.0,0.0);    
    //giro alrededor del sol
    glRotated(ang, 0.0,1.0,0.0);    
    //posicionamiento
    glTranslated(venusSun,0.0,0.0);    
    glutSolidSphere(0.05,50,50); 
    glPopMatrix();
}

void dibujarTierra(double ang){
    //Material 
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, earth_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glPushMatrix();    
    //giro alrededor del sol
    glRotated(ang, 0.0,1.0,0.0);
    //posicionamiento
    glTranslated(earthSun,0.0,0.0);        
    glutSolidSphere(0.05,50,50); 
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
    glRotated(-angM,0.0,1.0,0.0);
    glTranslated(-earthSun,0.0,0.0);     
    //posicionamiento
    glTranslated(earthSun+moonEarth,0.0,0.0);    
    glutSolidSphere(0.0125,50,50);    
    glPopMatrix();    
}

void dibujarMarte(double ang){
    //Material 
    glMaterialfv(GL_FRONT, GL_AMBIENT, mars_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mars_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mars_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glPushMatrix();
    glColor3f(1.0f,0.3f,0.0f);    
    //inclinacion del plano orbital
    glRotated(1.85, 1.0,0.0,0.0);    
    //giro alrededor del sol
    glRotated(ang, 0.0,1.0,0.0);
    //posicionamiento
    glTranslated(marsSun,0.0,0.0);        
    glutSolidSphere(0.0265,50,50); 
    glPopMatrix();
}

void dibujarJupiter(double ang){
    //Material 
    glMaterialfv(GL_FRONT, GL_AMBIENT, jupiter_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, jupiter_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, jupiter_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glPushMatrix();    
    //inclinacion del plano orbital
    glRotated(1.31, 1.0,0.0,0.0);    
    //giro alrededor del sol
    glRotated(ang, 0.0,1.0,0.0);
    //posicionamiento
    glTranslated(jupiterSun,0.0,0.0);    
    glutSolidSphere(0.5486,50,50); 
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
    glPopMatrix();
}

void dibujarUrano(double ang){
    //Material 
    glMaterialfv(GL_FRONT, GL_AMBIENT, uranus_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, uranus_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, uranus_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glPushMatrix();  
    //inclinacion del plano orbital
    glRotated(0.77, 1.0,0.0,0.0);    
    //giro alrededor del sol
    glRotated(ang, 0.0,1.0,0.0);
    //posicionamiento
    glTranslated(uranusSun,0.0,0.0);      
    glutSolidSphere(0.199,50,50); 
    glPopMatrix();
}

void dibujarNeptuno(double ang){
    //Material 
    glMaterialfv(GL_FRONT, GL_AMBIENT, neptune_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, neptune_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, neptune_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glPushMatrix();   
    //inclinacion del plano orbital
    glRotated(1.77, 1.0,0.0,0.0);    
    //giro alrededor del sol
    glRotated(ang, 0.0,1.0,0.0);
    //posicionamiento
    glTranslated(neptuneSun,0.0,0.0);    
    glutSolidSphere(0.1932,50,50); 
    glPopMatrix();
}

void funIdle(){
    
    angleMercury = angleMercury+2.073*speed;
    angleVenus = angleVenus+0.81*speed;
    angleEarth = angleEarth+0.5*speed;
    angleMoon = angleMoon+6.76*speed;
    angleMars = angleMars+0.265*speed;
    angleJupiter = angleJupiter+0.0426*speed;
    angleSaturn = angleSaturn+0.01697*speed;
    angleUranus = angleUranus+0.00595*speed;
    angleNeptune = angleNeptune+0.003030*speed;

    glutPostRedisplay();
}

void funKeyboard(unsigned char key, int x, int y){
     switch(key) {
        case 's':
            if ((angYCam/(2*PI/360)<179)){
                angYCam = angYCam + 2*PI/360;
            }
            break;
        case 'w':
            if ((angYCam/(2*PI/360)>1)){
                angYCam = angYCam - 2*PI/360;
            }
            break;
        case 'd':
            angXCam = angXCam - 5*(2*PI/360);
            break;
        case 'a':
            angXCam = angXCam + 5*(2*PI/360);
            break;
        case 'o':
            radiusCam = radiusCam + 0.8;
            break;
        case 'i':
            if (radiusCam>=1.5){
                radiusCam = radiusCam - 0.8;
            }
            break;
        case '+':
            if (speed < 10.0){
                speed = speed + 0.5;
            }
            break;
        case '-':
            if (speed > -10.0){
                speed = speed - 0.5;
            }
            break;
         case ' ':
             showOrbit=!showOrbit;
            break;
    }
    
    zCam = sin(angYCam)*sin(angXCam)*radiusCam;
    xCam = sin(angYCam)*cos(angXCam)*radiusCam;
    yCam = cos(angYCam)*radiusCam;
    
    glutPostRedisplay();
}


    

