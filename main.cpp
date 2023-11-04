#include <GL/glut.h>

void display(void);

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,300);
    glutInitWindowSize(400,400);
    glutCreateWindow("Hello OpenGL");

    glutDisplayFunc(display);

    glutMainLoop();

    return (0);
}

void display(void)
{

    glClearColor(0, 0, 0, 1);

    // clear the display using the clear color         
    glClear(GL_COLOR_BUFFER_BIT);

    // start drawing a polygon
    glBegin(GL_POLYGON);
        // set the paint color to red and draw a vertex
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.5f, 0.0f);
        // blue corner 
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.0f, 0.5f);
        // green corner
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.5f, 0.0f);
    // finish the polygon
    glEnd();

    // send the polygon data for rendering on the window
    glFlush();
}

