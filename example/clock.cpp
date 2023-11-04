#include <GL/glut.h>
#include <math.h>

GLshort time[3] = { 0, 8, 20 }; // hh:mm:ss format
GLfloat angle[3] = { 0.0f, -240.0f, -120.0f }; // represents angles for hh:mm:ss
GLshort dt = 1000; // one (1) second

// limit angle to lie between -180 and 180
GLfloat limitAngle(GLfloat angle)
{
    if (angle > 180.0f) return -((2.0f*180.0f) - angle);
    if (angle < -180.0f) return (2.0f*180.0f) + angle;
    return angle;
}

// compute time and update angles for each hand
void updateTime(int tick)
{
    time[2] += tick;
    angle[2] -= 6.0f;
    if (time[2] == 60) {
        time[2] = 0;
        ++time[1];
        angle[1] -= 6.0f;
        if (time[1] == 60) {
            time[1] = 0;
            ++time[0];
            angle[0] -= 6.0f;
        }
    }
    // limit the angles
    angle[0] = limitAngle(angle[0]);
    angle[1] = limitAngle(angle[1]);
    angle[2] = limitAngle(angle[2]);
    // request a display update
    glutPostRedisplay();
    glutTimerFunc(dt, updateTime, 1);
}

// function draw a single hand in a given direction
void drawClockHand(GLfloat angle, GLfloat height = 0.5f, GLfloat size = 0.005f)
{
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-size, height);
        glVertex2f(size, height);
        glVertex2f(size, 0.0f);
        glVertex2f(-size, 0.0f);
    glEnd();
    glPopMatrix();
}

// function that draws a circle
void drawCircle(GLfloat x, GLfloat y, GLfloat r)
{
   glPushMatrix();
   glTranslatef(x, y, 0.0f);
   glBegin(GL_TRIANGLE_FAN);
   	glVertex2f(0.0f, 0.0f);
   	for(GLfloat i = -180.0f; i < 180.0f; i += 6.0f)
	{
	    glVertex2f(r * cos(i), r * sin(i));
	}
   glEnd();
   glPopMatrix();
}

// function invoked when there are no events captured
void idle(void)
{
    glutPostRedisplay();
}

// function that display all hands of the clock 
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // circular frame
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.0f, 0.0f, 0.6f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.0f, 0.0f, 0.59f);

    // hour hand - red
    glColor3f(1.0f, 0.0f, 0.0f);
    drawClockHand(angle[0], 0.25f, 0.0075f);

    // minute hand - green
    glColor3f(0.0f, 1.0f, 0.0f);
    drawClockHand(angle[1], 0.35f);

    // seconds hand - blue
    glColor3f(0.0f, 0.0f, 1.0f);
    drawClockHand(angle[2], 0.5f, 0.0025f);

    // centered dot
    glColor3f(10.0f, 10.0f, 10.0f);
    drawCircle(0.0f, 0.0f, 0.015f);

    glutSwapBuffers();
}

// function invoked when the window is resized
void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width >= height) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

int main(int argc, char **argv)
{
    // initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // double buffer for smooth animation

    // create a window
    glutInitWindowPosition(500, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Clock");

    // register event callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutTimerFunc(0, updateTime, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // run
    glutMainLoop();

    return (0);
}
