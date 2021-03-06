#include <GL/gl.h> //include the gl header file
#include <GL/glut.h> //include the glut header file

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}

void display (void) {
glClearColor (0.0,0.0,0.0,1.0); //clear the color of the window
glClear (GL_COLOR_BUFFER_BIT); //Clear teh Color Buffer (more buffers later )
//glLoadIdentity(); //load the Identity Matrix
//gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //set the view

glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f,0.1f);
	glVertex2f(-0.2f,0.1f);
	glVertex2f(-0.2f,0.7f);
	glVertex2f(-1.0f,0.7f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f,0.1f);
	glVertex2f(0.0f,0.0f);
	glVertex2f(0.1f,00.0f);
	glVertex2f(0.1f,0.1f);
glEnd();

glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.4f,0.2f);
	glVertex2f(0.6f,0.2f);
	glVertex2f(0.7f,0.4f);
	glVertex2f(0.6f,0.6f);	
	glVertex2f(0.4f,0.6f);
	glVertex2f(0.3f,0.4f);
	
glEnd();

glFlush(); //flush it all to the screen
}

int main (int argc, char **argv) {
glutInit (&argc, argv); //initialize the program.
glutInitDisplayMode (GLUT_SINGLE); //set up a basic display buffer (only singular for now)
glutInitWindowSize (500, 500); //set whe width and height of the window
glutInitWindowPosition (100, 100); //set the position of the window
glutCreateWindow ("A basic OpenGL Window"); //set the caption for the window
glutDisplayFunc (display); //call the display function to draw our world
glutReshapeFunc (reshape); // call the reshape function to reshape your window
glutIdleFunc (display);
glutMainLoop (); //initialize the OpenGL loop cycle
return 0;
}
