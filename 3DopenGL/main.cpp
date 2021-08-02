/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#include<GL/gl.h>
#include<stdio.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <string.h>
#define ESCAPE 27
/* ASCII code for the escape key. */

using namespace std;

GLint window;
GLint Xsize=1000;
GLint Ysize=800;

GLfloat xt=0.0,yt=0.0,zt=0.0,xw=0.0;   /* x,y,z translation */ //to be able to do the translation
GLfloat xs=1.0,ys=1.0,zs=1.0;
GLfloat xangle=15.0,yangle=0.0,zangle=0.0,angle=0.0;   /* axis angles */
GLfloat r=1,g=0,b=1;
GLUquadricObj *t;
GLuint makeaTree; //unsigned int
bool open = 0;
//float x,y,z;

void makeCylinder(float Height, float Base){
    GLUquadric *obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_FILL);
    glColor3f(0.3f,0.4f,0.2f);
    glPushMatrix();
    glRotatef(-90, 1.0,0.0,0.0);
    gluCylinder(obj, Base,Base-(0.2*Base), Height, 20,20); //structure or filling of the cylinders
    glPopMatrix();
    glutSwapBuffers();
}

void makeTree(float Height, float Base){
    float angle;
    makeCylinder(Height, Base);
    glTranslatef(0.0, Height, 0.0);
    Height -= Height*.2;
    Base-= Base*0.3;
    for(int a= 0; a<3; a++){
        angle = rand()%50+20;
        if(angle >48)
            angle = -(rand()%50+20);
        if (Height >1){
            glPushMatrix();
            glRotatef(angle,1,0.0,1);
            makeTree(Height,Base);
            glPopMatrix();
        }
        else
            glColor3f(0.0f,0.8f,0.0f);
            glutSolidSphere(0.2,10,10); //leaves
}

}
void initTree(void)
{
    glClearColor(0.7, 0.9, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    makeaTree = glGenLists(1); //range of empty display sets, reserve places for future use
    glNewList(makeaTree, GL_COMPILE);
    makeTree(4.0, 0.2);
    glEndList();
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//static void SpecialKeyFunc( int Key, int x, int y );

/* Simple  transformation routine */
GLvoid Transform(GLfloat Width, GLfloat Height)
{
  glViewport(0, 0, Width, Height);              /* Set the viewport */
  glMatrixMode(GL_PROJECTION);                  /* Select the projection matrix */
  glLoadIdentity();				/* Reset The Projection Matrix using identity matrix */
  gluPerspective(45.0,Width/Height,0.1,100.0);  /* Calculate The Aspect Ratio Of The Window */
  glMatrixMode(GL_MODELVIEW);                   /* Switch back to the modelview matrix */
}


/* A general OpenGL initialization function.  Sets all of the initial parameters. */
GLvoid InitGL(GLfloat Width, GLfloat Height)
{
  glClearColor(0.7, 0.9, 1.0, 0.0);
    glLineWidth(2.0);              /* Add line width */
    Transform(Width, Height); /* Perform the transformation */
    //newly added
    t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };


    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

/* The function called when our window is resized  */
GLvoid ReSizeGLScene(GLint Width, GLint Height)
{
  if (Height==0)     Height=1;                   /* Sanity checks */
  if (Width==0)      Width=1;
  Transform( Width, Height );                   /* Perform the transformation */
}


/* The main drawing function

   In here we put all the OpenGL and calls to routines which manipulate
   the OpenGL state and environment.

   This is the function which will be called when a "redisplay" is requested.
*/

GLvoid DrawGLScene()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef( xs,xs,1.0f );
    glRotatef(xangle,-1.0f, 1.5f, -5.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/* Clear The Screen And The Depth Buffer */

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-1.0,0.0,-3.5);
    glRotatef(xangle,1.0,0.0,0.0);
    glRotatef(yangle,0.0,1.0,0.0);
    glRotatef(zangle,0.0,0.0,1.0);
    glTranslatef(xt,yt,zt);
    glScalef(xs,ys,zs);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //tree objects
    glPushMatrix();
    glScalef(xs,xs,1.0);
    glTranslatef(-5.0,0.0,-25.5);
    glCallList(makeaTree);
    glPopMatrix();

    glPushMatrix();
    glScalef(xs,xs,1.0);
    glTranslatef(-12.0,0.0,10.0);
    glCallList(makeaTree);
    glPopMatrix();
    //
    glColor3f(1.0,.75,0.0);
    glPointSize(30.0);
    glBegin(GL_POINTS);
    glVertex3f(0.2,0.3,0.3);
    glVertex3f(0.2,0.3,0.5);
    glEnd();
    glPointSize(200.0);

    glBegin(GL_QUADS);                /* OBJECT MODULE Start drawing the cars and the surroundings*/
  /* top of cube*/
  //*********FRONT BODY*************
    glColor3f(r, g, b);
    glVertex3f(0.2, 0.4, 0.6);
    glVertex3f(0.6, 0.5, 0.6);
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.2, 0.4, 0.2);

    /* bottom of cube*/
    glVertex3f(0.2, 0.2, 0.6);
    glVertex3f(0.6, 0.2, 0.6);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(0.2, 0.2, 0.2);

    /* front of cube*/
    glVertex3f(0.2, 0.2, 0.6);
    glVertex3f(0.2, 0.4, 0.6);
    glVertex3f(0.2, 0.4, 0.2);
    glVertex3f(0.2, 0.2, 0.2);

    /* back of cube.*/
    glVertex3f(0.6, 0.2, 0.6);
    glVertex3f(0.6, 0.5, 0.6);
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.6, 0.2, 0.2);

    /* left of cube*/
    glVertex3f(0.2, 0.2, 0.6);
    glVertex3f(0.6, 0.2, 0.6);
    glVertex3f(0.6, 0.5, 0.6);
    glVertex3f(0.2, 0.4, 0.6);

    /* Right of cube */
    glVertex3f(0.2, 0.2, 0.2);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.2, 0.4, 0.2);

//**************************
    glVertex3f(0.7, 0.65, 0.6);
    glVertex3f(0.7, 0.65, 0.2);
    glVertex3f(1.7, 0.65, 0.2);        //top cover
    glVertex3f(1.7, 0.65, 0.6);
//**********back guard*********** the back end of the car
    glColor3f(r, g, b);           //set the colour of the car
    glVertex3f(1.8, 0.5, 0.6);
    glVertex3f(1.8, 0.5, 0.2);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1, 0.4, 0.6);

    /* bottom of cube*/
    glVertex3f(2.1, 0.2, 0.6);
    glVertex3f(2.1, 0.2, 0.2);
    glVertex3f(1.8, 0.2, 0.6);
    glVertex3f(1.8, 0.2, 0.6);

    /* back of cube.*/
    glVertex3f(2.1, 0.4, 0.6);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1, 0.2, 0.2);
    glVertex3f(2.1, 0.2, 0.6);

    /* left of cube*/
    glVertex3f(1.8, 0.2, 0.2);
    glVertex3f(1.8, 0.5, 0.2);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1, 0.2, 0.2);

    /* Right of cube */
    glVertex3f(1.8, 0.2, 0.6);
    glVertex3f(1.8, 0.5, 0.6);
    glVertex3f(2.1, 0.4, 0.6);
    glVertex3f(2.1, 0.2, 0.6);
    //**MIDDLE BODY****

//*******MIDDLE BODY*************

    if (!open) {
        // Closed doors
        glVertex3f(0.6, 0.5, 0.6);
        glVertex3f(0.6, 0.2, 0.6);
        glVertex3f(1.8, 0.2, 0.6);
        glVertex3f(1.8, 0.5, 0.6);
        /* back of cube.*/
        glVertex3f(0.6,0.5,0.2);
        glVertex3f(0.6,0.2,0.2);
        glVertex3f(1.8,0.2,0.2);
        glVertex3f(1.8,0.5,0.2);
        /* bottom of cube*/
        glVertex3f( 0.6,0.2,0.6);
        glVertex3f(0.6,0.2,0.2);
        glVertex3f(1.8,0.2,0.2);
        glVertex3f( 1.8,0.2,0.6);
    }
    else {

        //back door
        glColor3f(1, 0, 1);
        glVertex3f(1.2, 0.5, 0.5);
        glVertex3f(1.2, 0.2, 0.5);
        glVertex3f(1.22, 0.2, 1);
        glVertex3f(1.22, 0.5, 1);

        //front door
        glColor3f(1, 0, 1);
        glVertex3f(0.7, 0.5, 0.5);
        glVertex3f(0.7, 0.2, 0.5);
        glVertex3f(0.7, 0.2, 1);
        glVertex3f(0.7, 0.5, 1);

        /* back of cube.*/
        //for purple outside
        glColor3f(1, 0, 1);
        glVertex3f(0.6, 0.5, 0.2);
        glVertex3f(0.6, 0.2, 0.2);
        glVertex3f(1.8, 0.2, 0.2);
        glVertex3f(1.8, 0.5, 0.2);
        //for black inside
        glColor3f(0, 0, 0);
        glVertex3f(0.6, 0.5, 0.21);
        glVertex3f(0.6, 0.2, 0.21);
        glVertex3f(1.8, 0.2, 0.21);
        glVertex3f(1.8, 0.5, 0.21);
         /* bottom of cube*/
        glVertex3f( 0.6,0.2,0.6);
        glVertex3f(0.6,0.2,0.2);
        glVertex3f(1.8,0.2,0.2);
        glVertex3f( 1.8,0.2,0.6);
    }
//********ENTER WINDOW***********
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.77, 0.63, 0.2);
    glVertex3f(0.75, 0.5, 0.2);        //quad front window
    glVertex3f(1.2, 0.5, 0.2);
    glVertex3f(1.22, 0.63, 0.2);

    glVertex3f(1.27, 0.63, .2);
    glVertex3f(1.25, 0.5, 0.2);        //quad back window
    glVertex3f(1.65, 0.5, 0.2);
    glVertex3f(1.67, 0.63, 0.2);

    glColor3f(0, 0,0);
    glVertex3f(0.7, 0.65, 0.2);
    glVertex3f(0.7, 0.5, .2);       //first separation
    glVertex3f(0.75, 0.5, 0.2);
    glVertex3f(0.77, 0.65, 0.2);

    glVertex3f(1.2, 0.65, 0.2);
    glVertex3f(1.2, 0.5, .2);       //second separation
    glVertex3f(1.25, 0.5, 0.2);
    glVertex3f(1.27, 0.65, 0.2);

    glVertex3f(1.65, 0.65, 0.2);
    glVertex3f(1.65, 0.5, .2);     //3d separation
    glVertex3f(1.7, 0.5, 0.2);
    glVertex3f(1.7, 0.65, 0.2);

    glColor3f(0, 0, 0);
    glVertex3f(0.75, 0.65, 0.2);
    glVertex3f(0.75, 0.63, 0.2);        //line strip
    glVertex3f(1.7, 0.63, 0.2);
    glVertex3f(1.7, 0.65, 0.2);

    glVertex3f(0.75, 0.65, 0.6);
    glVertex3f(0.75, 0.63, 0.6);        //line strip
    glVertex3f(1.7, 0.63, 0.6);
    glVertex3f(1.7, 0.65, 0.6);

    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.77, 0.63, 0.6);
    glVertex3f(0.75, 0.5, 0.6);        //quad front window
    glVertex3f(1.2, 0.5, 0.6);
    glVertex3f(1.22, 0.63, 0.6);

    glVertex3f(1.27, 0.63, .6);
    glVertex3f(1.25, 0.5, 0.6);        //quad back window
    glVertex3f(1.65, 0.5, 0.6);
    glVertex3f(1.67, 0.63, 0.6);

    glColor3f(0, 0, 0);
    glVertex3f(0.7, 0.65, 0.6);
    glVertex3f(0.7, 0.5, .6);       //first separation l far2 mben l 3arbya wl windows
    glVertex3f(0.75, 0.5, 0.6);
    glVertex3f(0.77, 0.65, 0.6);

    glVertex3f(1.2, 0.65, 0.6);
    glVertex3f(1.2, 0.5, .6);       //second separation
    glVertex3f(1.25, 0.5, 0.6);
    glVertex3f(1.27, 0.65, 0.6);

    glVertex3f(1.65, 0.65, 0.6);
    glVertex3f(1.65, 0.5, .6);
    glVertex3f(1.7, 0.5, 0.6);
    glVertex3f(1.7, 0.65, 0.6);
    glEnd();
 //**********************
  glBegin(GL_QUADS);

  /* top of cube*/
  glColor3f(0.3,0.3,0.3);
  glVertex3f( 0.6, 0.5,0.6);
  glVertex3f(0.6, 0.5,0.2);        //quad front window, the big part of the front window
  glVertex3f(0.7, 0.65, 0.2);
  glVertex3f( 0.7,0.65,0.6);

  glVertex3f(1.7,0.65,0.6);
  glVertex3f(1.7,0.65,0.2);        //quad back window, the big part of the back window
  glVertex3f(1.8,0.5,0.2);
  glVertex3f(1.8,0.5,0.6);


//**********road and surrounding development************

  glPushMatrix();
  glTranslatef(xw,0,0);
  glColor3f(0,1,0);
  glVertex3f(-100,0.1,-100);
  glVertex3f(-100,0.1,0);         //a green surroundings, the upper one
  glVertex3f(100,0.1,0);
  glVertex3f(100,0.1,-100);

  glColor3f(0.7,0.7,0.7);
  glVertex3f(-100,0.1,0);
  glVertex3f(-100,0.1,0.45);         //a long road
  glVertex3f(100,0.1,0.45);
  glVertex3f(100,0.1,0);

  glColor3f(1.0,0.75,0.0);
  glVertex3f(-100,0.1,0.45);       //a median
  glVertex3f(-100,0.1,0.55);
  glVertex3f(100,0.1,0.55);
  glVertex3f(100,0.1,0.45);

  glColor3f(0.7,0.7,0.7);
  glVertex3f(-100,0.1,0.55);
  glVertex3f(-100,0.1,1);         //a long road
  glVertex3f(100,0.1,1);
  glVertex3f(100,0.1,0.55);

  glColor3f(0,1,0);
  glVertex3f(-100,0.1,1);
  glVertex3f(-100,0.1,100);         //a green surroundings, the lower one
  glVertex3f(100,0.1,100);
  glVertex3f(100,0.1,1);
  glPopMatrix();

  glEnd();
//*********************************
  glBegin(GL_TRIANGLES);                /* start drawing the cube.*/

  /* top of cube*/
  glColor3f(0.3,0.3,0.3);
  glVertex3f( 0.6, 0.5,0.6);
  glVertex3f( 0.7,0.65,0.6);       //triangle front window
  glVertex3f(0.7,0.5,0.6);

  glVertex3f( 0.6, 0.5,0.2);
  glVertex3f( 0.7,0.65,0.2);       //triangle front window
  glVertex3f(0.7,0.5,0.2);

  glVertex3f( 1.7, 0.65,0.2);
  glVertex3f( 1.8,0.5,0.2);       //triangle back window
  glVertex3f( 1.7,0.5,0.2);

  glVertex3f( 1.7, 0.65,0.6);
  glVertex3f( 1.8,0.5,0.6);       //triangle back window
  glVertex3f(1.7,0.5,0.6);

  glEnd();
//*******WHEEL****************
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0.6, 0.2, 0.6);
    glColor3f(0, 0, 0);
    glutSolidTorus(0.025, 0.07, 10, 25);

    glTranslatef(0, 0, -0.4);
    glutSolidTorus(0.025, 0.07, 10, 25);

    glTranslatef(1.1, 0, 0);
    glutSolidTorus(0.025, 0.07, 10, 25);

    glTranslatef(0, 0, 0.4);
    glutSolidTorus(0.025, 0.07, 10, 25);

    glPopMatrix();
//*********************
  glPopMatrix();
  glEnable(GL_DEPTH_TEST);
  glutPostRedisplay();
  glutSwapBuffers();
 }



/*  The function called whenever a "normal" key is pressed. */
void NormalKey(GLubyte key, GLint x, GLint y)
{
    switch (key) {
    case ESCAPE:
        printf("Escape pressed. Exit.\n");
        glutDestroyWindow(window);
        exit(0);
        break;

    case 'y':
        yangle += 5.0;
        glutPostRedisplay();
        break;
    case 'Y':
        yangle -= 5.0;
        glutPostRedisplay();
        break;

    case 'u':                          /* Move up */
        yt += 0.2;
        glutPostRedisplay();
        break;
    case 'U':
        yt -= 0.2;                      /* Move down */
        glutPostRedisplay();
        break;

    case 's':
        zs += .2;                       //scale according to z
        glutPostRedisplay();
        break;

    case 'S':                           //scale according to z
        zs -= 0.2;
        glutPostRedisplay();
        break;

    case 'a':                           //bigger height, scale according to y
        ys += .2;
        glutPostRedisplay();
        break;

    case 'A':                           //smaller height, scale according to y
        ys -= 0.2;
        glutPostRedisplay();
        break;

    case 'q':                           //bigger width
        xs += .2;
        glutPostRedisplay();
        break;

    case 'Q':                           //smaller width
        xs -= 0.2;
        glutPostRedisplay();
        break;
    case 'o':                           //close door
        open = 1;
        glutPostRedisplay();
        break;

    case 'O':                           //close door
        open = 0;
        glutPostRedisplay();
        break;

     default:
	break;
    }

}
void mouse(int button,int state, int mousex, int mousey)
{
    if(button==GLUT_RIGHT_BUTTON){      //move car to the right
		xt += 0.1;
		angle+=3;
		xw+=0.1;
	    glutPostRedisplay();
	}
    else if (button==GLUT_LEFT_BUTTON){      //move car to the left
    	xt -= 0.1;
		angle+=3;
		xw-=0.1;
		glutPostRedisplay();
    }
}
static void SpecialKeyFunc( int Key, int x, int y )
{
	switch ( Key ) {

    case GLUT_KEY_UP:      //zoom in
        zt+= 0.15;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:     //zoom out
        zt-= 0.15;
        glutPostRedisplay();
        break;
	}
}
//
//void myMenu(int id)
//{
//	if(id ==2)
//	{
//		xangle += 5.0;
//		glutPostRedisplay();
//	}
//}


//********* Main *********************

int main(int argc, char **argv)
{

/* Initialisation and window creation */

  glutInit(&argc, argv);               /* Initialize GLUT state. */

  glutInitDisplayMode(GLUT_RGBA |      /* RGB and Alpha */
                      GLUT_DOUBLE|     /* double buffer */
                      GLUT_DEPTH);     /* Z buffer (depth) */

  glutInitWindowSize(Xsize,Ysize);     /* set initial window size. */
  glutInitWindowPosition(0,0);         /* upper left corner of the screen. */

  glutCreateWindow("Garden Car Animated"); /* Open a window with a title. */

/* Now register the various callback functions */

  glutDisplayFunc(DrawGLScene);        /* Function to do all our OpenGL drawing. */
  glutReshapeFunc(ReSizeGLScene);
  glutKeyboardFunc(NormalKey);         /*Normal key is pressed */
  glutSpecialFunc( SpecialKeyFunc );
  glutMouseFunc(mouse);
  InitGL(Xsize,Ysize);
  initTree();
  //myMenu(2);
  /* Now drop into the event loop from which we never return */

  glutMainLoop();                      /* Start Event Processing Engine. */
  return 1;
}
