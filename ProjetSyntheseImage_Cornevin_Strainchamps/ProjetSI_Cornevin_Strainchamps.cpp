/****************************************************************************************/
/*                     cube.cpp                    */
/****************************************************************************************/
/*         Affiche a l'ecran un cube en 3D         */
/****************************************************************************************/

/* inclusion des fichiers d'en-tete freeglut */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <cstdlib>
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>
#include <cmath>
#include <iostream>

//constantes liées aux textures
const unsigned int largimg1 = 800;
const unsigned int hautimg1 = 800;
unsigned char image1[largimg1*hautimg1*3];
const unsigned int largimg2 = 584;
const unsigned int hautimg2 = 400;
unsigned char image2[largimg2*hautimg2*3];
GLuint texObject[2]; // objet tableau de textures

//constantes liées aux animations
int direction = 1; // 1 pour incrémenter, -1 pour décrémenter
float angleOreille=10;
float angleMoustache=10;

char presse;
int anglex,angley,x,y,xold,yold;

//constantes liées à la caméra
float rayonCamera = 5;
float angleCamera = 0;
float angleCamera2 = 0;

/* Prototype des fonctions */
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void loadJpegImage(char *fichier,unsigned char *image, int largimg, int hautimg);
void sphereTexture(float r, int nbM, int nbP);

int main(int argc,char **argv)
{
    /* Chargement des textures */
    loadJpegImage("./textures/satin.jpeg", image1, largimg1, hautimg1); //pour la cape
    loadJpegImage("./textures/fourrure.jpg", image2, largimg2, hautimg2); //pour la fourrure

    /* initialisation de glut et creation
     de la fenetre */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(800,800);
    glutCreateWindow("Lapin");

    /* Initialisation d'OpenGL */
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    /* Paramétrage des textures */
    glGenTextures(2, texObject); // génère un nouvel objet de texture

    // Lierla texture 1 qui est le tissu pour la cape
    glBindTexture(GL_TEXTURE_2D, texObject[0]);
    // Paramètres de la texture 1
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,largimg1,hautimg1,0,
                 GL_RGB,GL_UNSIGNED_BYTE,image1);

    // Lier la texture 2 qui est la fourrure du lapin
    glBindTexture(GL_TEXTURE_2D, texObject[1]);
    // Paramètres de la texture 2
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,largimg2,hautimg2,0,
                 GL_RGB,GL_UNSIGNED_BYTE,image2);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_DECAL);

    // paramétrage de la lumière

    //première lumière (lumière générale)
    GLfloat mat_specular[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat mat_shininess[] = { 10.0 };
    GLfloat light_position[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat light_ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};   // Lumière ambiante
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};   // Lumière diffuse
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Lumière spéculaire

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    //deuxième lumière (projecteur)
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);



    /* enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);

    glutIdleFunc(idle);

    /* Entree dans la boucle principale glut */
    glutMainLoop();

    return 0;
}

//fonction qui dessine le lapin
void affichage()
{
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(-20, 20, -20, 20, -20, 20) ;
  glMatrixMode(GL_MODELVIEW);
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);

  // point de vue de l'utilisateur
  gluLookAt(rayonCamera*cos(angleCamera)*cos(angleCamera2), rayonCamera*sin(angleCamera2), rayonCamera*sin(angleCamera)* cos(angleCamera2),  // Position de la caméra
              0.0, 0.0, 0.0,  // Point de vue (regardé vers l'origine)
              0.0, 1.0, 0.0);  // Vecteur d'orientation vers le haut (l'axe y)


    //Tête
    glPushMatrix();
    glScalef(1, 0.90, 1);
    glColor3f(1.0f,1.0f,1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObject[1]);
    sphereTexture(4.0, 50, 50);
    //glutSolidSphere(4,50, 50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //Joues
    glColor3f(1, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(-2,-1.5,2);
    glutSolidSphere(1.5,50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,-1.5,2);
    glutSolidSphere(1.5,50, 50);
    glPopMatrix();

    //Dents
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-0.2,-2,3.5);
    glScalef(0.5, 1, 0.5);
    glutSolidCube(0.75);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2,-2,3.5);
    glScalef(0.5, 1, 0.5);
    glutSolidCube(0.75);
    glPopMatrix();

    //Yeux
    glColor3f(1, 0.95, 0.95);
    glPushMatrix();
    glTranslatef(-1.5,1.5,2.5);
    glutSolidSphere(1,50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,1.5,2.5);
    glutSolidSphere(1,50, 50);
    glPopMatrix();

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(-1.6,1.6,3.2);
    glutSolidSphere(0.5,50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.6,1.6,3.2);
    glutSolidSphere(0.5,50, 50);
    glPopMatrix();
    glColor3f(1, 1, 1);

    //Moustaches droite
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(1.20,-1.4,4.5);
    glRotatef(angleMoustache, 0, -1, 0);
    glScalef(2, 0.05, 0.05);
    glutSolidCube(1.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.15,-1.55,4.5);
    glRotatef(10, 0, 0, -1);
    glRotatef(angleMoustache, 0, -1, 0);
    glScalef(2, 0.05, 0.05);
    glutSolidCube(1.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.15,-1.25,4.5);
    glRotatef(10, 0, 0, 1);
    glRotatef(angleMoustache, 0, -1, 0);
    glScalef(2, 0.05, 0.05);
    glutSolidCube(1.25);
    glPopMatrix();

    //Moustaches gauche
    glPushMatrix();
    glTranslatef(-1.20,-1.4,4.5);
    glRotatef(angleMoustache, 0, 1, 0);
    glScalef(2, 0.05, 0.05);
    glutSolidCube(1.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.15,-1.55,4.5);
    glRotatef(angleMoustache, 0, 1, 0);
    glRotatef(10, 0, 0, 1);
    glScalef(2, 0.05, 0.05);
    glutSolidCube(1.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.15,-1.25,4.5);
    glRotatef(10, 0, 0, -1);
    glRotatef(angleMoustache, 0, 1, 0);
    glScalef(2, 0.05, 0.05);
    glutSolidCube(1.25);
    glPopMatrix();

    glColor3f(1, 0.89, 0.77);

    //Nez
    glColor3f(1, 0.95, 0.95);
    glPushMatrix();
    glTranslatef(0,-0.5,4);
    glScalef(1.5, 0.75, 0.75);
    glutSolidSphere(1,50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,-0.75,4);
    glutSolidSphere(1,50, 50);
    glPopMatrix();

    //Oreille droite
    glPushMatrix();
    glTranslatef(1.5,3.5,0);
    glRotatef(angleOreille, 0, 0, -1);
    glRotatef(-20, 0, 1, 0);
    glScalef(0.25, 1.5, 0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObject[1]);
    sphereTexture(4.0, 50, 50);
    //glutSolidSphere(4,50, 50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Oreille gauche
    glPushMatrix();
    glTranslatef(-1.5,3.5,0);
    glRotatef(angleOreille, 0, 0, 1);
    glRotatef(-20, 0, -1, 0);
    glScalef(0.25, 1.5, 0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObject[1]);
    sphereTexture(4.0, 50, 50);
    //glutSolidSphere(4,50, 50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //corps
    glPushMatrix();
    glTranslatef(0, -10, 0);
    glScalef(1, 1.5, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObject[1]);
    sphereTexture(5.0, 50, 50);
    //glutSolidSphere(5,50, 50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //queue
    glPushMatrix();
    glTranslatef(0,-12,-5);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObject[1]);
    sphereTexture(1.5, 50, 50);
    //glutSolidSphere(1.5,50, 50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //pates avant
    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslatef(-2,-8,3.5);
    glRotatef(40, -1, 0, 0);
    glScalef(1,1.5,0.5);
    glutSolidSphere(2,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,-8,3.5);
    glRotatef(40, -1, 0, 0);
    glScalef(1,1.5,0.5);
    glutSolidSphere(2,50,50);
    glPopMatrix();

    //pates arrieres
    glPushMatrix();
    glTranslatef(-2,-17,2);
    glScalef(1,0.5,2);
    glutSolidSphere(2,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,-17,2);
    glScalef(1,0.5,2);
    glutSolidSphere(2,50,50);
    glPopMatrix();


    //cape
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0,-4.2,0);
    glScalef(1.8, 0.01, 1.8);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObject[0]);
    sphereTexture(2.0, 50, 50);
    //glutSolidSphere(2,50,50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-7.5,-6);
    glRotatef(40, 1, 0, 0);
    glScalef(1.5, 3, 0.05);
    //texture sur les cube de la cape
    glEnable(GL_TEXTURE_2D);//on active la texture
    glBindTexture(GL_TEXTURE_2D, texObject[0]);// on choisit notre texture dans notre tableau de texture
    glBegin(GL_POLYGON);//on commence l'appareillage d'un sommet de notre image avec un sommet de notre cube
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.5, -1.5, -1.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.5, 1.5, -1.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.5, 1.5, -1.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.5, -1.5, -1.5);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.5, -1.5, 1.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.5, 1.5, 1.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.5, 1.5, 1.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.5, -1.5, 1.5);
    glEnd();
    glutSolidCube(3);
    glDisable(GL_TEXTURE_2D);//on désactive la texture
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.3,-7.5,-6);
    glRotatef(40, 1, 0, 0);
    glRotatef(45, 0, 0, 1);
    glScalef(1, 1, 0.05);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObject[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-3.15, -3.15, -3.15);
    glTexCoord2f(0.0, 1.0); glVertex3f(-3.15, 3.15, -3.15);
    glTexCoord2f(1.0, 1.0); glVertex3f(3.15, 3.15, -3.15);
    glTexCoord2f(1.0, 0.0); glVertex3f(3.15, -3.15, -3.15);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-3.15, -3.15, 3.15);
    glTexCoord2f(0.0, 1.0); glVertex3f(-3.15, 3.15, 3.15);
    glTexCoord2f(1.0, 1.0); glVertex3f(3.15, 3.15, 3.15);
    glTexCoord2f(1.0, 0.0); glVertex3f(3.15, -3.15, 3.15);
    glEnd();
    glutSolidCube(6.3);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.3,-7.5,-6);
    glRotatef(40, 1, 0, 0);
    glRotatef(45, 0, 0, -1);
    glScalef(1, 1, 0.05);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObject[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-3.15, -3.15, -3.15);
    glTexCoord2f(0.0, 1.0); glVertex3f(-3.15, 3.15, -3.15);
    glTexCoord2f(1.0, 1.0); glVertex3f(3.15, 3.15, -3.15);
    glTexCoord2f(1.0, 0.0); glVertex3f(3.15, -3.15, -3.15);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-3.15, -3.15, 3.15);
    glTexCoord2f(0.0, 1.0); glVertex3f(-3.15, 3.15, 3.15);
    glTexCoord2f(1.0, 1.0); glVertex3f(3.15, 3.15, 3.15);
    glTexCoord2f(1.0, 0.0); glVertex3f(3.15, -3.15, 3.15);
    glEnd();
    glutSolidCube(6.3);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-9.2,-7.4);
    glRotatef(40, 1, 0, 0);
    glScalef(3, 1, 0.05);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObject[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-2.25, -2.25, -2.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-2.25, 2.25, -2.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(2.25, 2.25, -2.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(2.25, -2.25, -2.25);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-2.25, -2.25, 2.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-2.25, 2.25, 2.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(2.25, 2.25, 2.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(2.25, -2.25, 2.25);
    glEnd();
    glutSolidCube(4.5);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //L sur la cape
    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslatef(1,-7.2,-6.2);
    glRotatef(40, 1, 0, 0);
    glScalef(1, 4, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-8.5,-7.2);
    glRotatef(40, 1, 0, 0);
    glScalef(3, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    //Repère
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(1, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    	glColor3f(0.0,1.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 1,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    	glColor3f(0.0,0.0,1.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 0,1.0);
    glEnd();

  glFlush();

  //On echange les buffers
  glutSwapBuffers();
}

//fonction qui dessine une sphere et enroule la texture dessus
void sphereTexture(float r, int nbM, int nbP) {

    for (int i = 0; i < nbM; i++) {
        glBegin(GL_QUADS);
        for (int j = 0; j <= nbP; j++) {
            float theta1 = (i * 2 * M_PI) / nbM;
            float phi1 = (j * M_PI) / nbP;
            float x1 = r * sin(phi1) * cos(theta1);
            float y1 = r * sin(phi1) * sin(theta1);
            float z1 = r * cos(phi1);

            float theta2 = ((i + 1) * 2 * M_PI) / nbM;
            float phi2 = (j * M_PI) / nbP;
            float x2 = r * sin(phi2) * cos(theta2);
            float y2 = r * sin(phi2) * sin(theta2);
            float z2 = r * cos(phi2);

            float theta3 = ((i + 1) * 2 * M_PI) / nbM;
            float phi3 = ((j+1) * M_PI) / nbP;
            float x3 = r * sin(phi3) * cos(theta3);
            float y3 = r * sin(phi3) * sin(theta3);
            float z3 = r * cos(phi3);

            float theta4 = (i * 2 * M_PI) / nbM;
            float phi4 = ((j+1) * M_PI) / nbP;
            float x4 = r * sin(phi4) * cos(theta4);
            float y4 = r * sin(phi4) * sin(theta4);
            float z4 = r * cos(phi4);

            //pour le point en haut à gauche (coin inférieur gauche de la texture)
            glNormal3f(x1, y1, z1);
            glTexCoord2f((float)i / nbM, (float)j / nbP);
            glVertex3f(x1, y1, z1);

            glNormal3f(x2, y2, z2);
            glTexCoord2f((float)(i + 1) / nbM, (float)j / nbP);
            glVertex3f(x2, y2, z2);

            glNormal3f(x3, y3, z3);
            glTexCoord2f((float)(i + 1) / nbM, (float)(j+1) / nbP);
            glVertex3f(x3, y3, z3);

            glNormal3f(x4, y4, z4);
            glTexCoord2f((float)i / nbM, (float)(j+1) / nbP);
            glVertex3f(x4, y4, z4);
        }
        glEnd();
    }
}

//fonction pour les animations clavier
void clavier(unsigned char touche,int x,int y)
{
  switch (touche) {
      case 'p': /* affichage du carre plein */
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
          glutPostRedisplay();
          break;
      case 'f': /* affichage en mode fil de fer */
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
          glutPostRedisplay();
          break;
      case 'a' : //dezoom
          rayonCamera += 5;
          break;
      case 'A' ://zoom
          if(rayonCamera>1) {
              rayonCamera -= 5;
          }
          break;
      case 'o' :
          if(angleOreille<=40) {
              angleOreille += 1;
              glutPostRedisplay();
          }
          break;
      case 'O' :
          if(angleOreille>=0) {
              angleOreille -= 1;
              glutPostRedisplay();
          }
          break;
      case 'l' :
          glClearColor (0.94, 0.87, 0.65, 0.0);
          glEnable(GL_LIGHTING);
          glEnable(GL_LIGHT0);
          break;
      case 'L' :
          glClearColor (0.0, 0.0, 0.0, 0.0);
          glDisable(GL_LIGHTING);
          glDisable(GL_LIGHT0);
          break;
      case 'm' :
          glEnable(GL_LIGHTING);
          glEnable(GL_LIGHT1);
          break;
      case 'M' :
          glClearColor (0.0, 0.0, 0.0, 0.0);
          glDisable(GL_LIGHTING);
          glDisable(GL_LIGHT1);
          break;
      case 'z':
          angleCamera2 += 0.3;
          break;
      case 's':
          angleCamera2 -= 0.3;
          break;
      case 'q':
          angleCamera -= 0.3;
          break;
      case 'd':
          angleCamera += 0.3;
          break;
      case 'k' : /*la touche 'k' permet de quitter le programme */
          exit(0);
    }
}

void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}

void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }

void loadJpegImage(char *fichier, unsigned char *image, int largimg, int hautimg) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
#ifdef __WIN32
    if (fopen_s(&file,fichier,"rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#elif __GNUC__
    if ((file = fopen(fichier, "rb")) == 0) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
#endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    /*if ((cinfo.image_width!=256)||(cinfo.image_height!=256)) {
      fprintf(stdout,"Erreur : l'image doit etre de taille 256x256\n");
      exit(1);
    }*/
    if (cinfo.jpeg_color_space == JCS_GRAYSCALE) {
        fprintf(stdout, "Erreur : l'image doit etre de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);
    ligne = image;
    while (cinfo.output_scanline < cinfo.output_height) {
        ligne = image + 3 * largimg * cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo, &ligne, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
}


void idle() {
    if (direction == 1) {
        angleMoustache += 1.0;
        if (angleMoustache > 30.0)
            direction = -1;
    } else {
        angleMoustache -= 1.0;
        if (angleMoustache < -5.0)
            direction = 1;
    }
    glutPostRedisplay(); // Demandez un rafraîchissement de l'affichage
}

