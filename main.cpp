#include <GL/glut.h>

void display(void);

int main(int argc, char* argv[])
{
    // initializes GLUT
    glutInit(&argc, argv);

    // set display mode (single buffer with RGB colors 
    // since there are no animations
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // set window initial position
    glutInitWindowPosition(200, 300);
    
    // set window initial size
    glutInitWindowSize(400, 400);

    // create the window with a title e.g "Hello OpenGL"
    glutCreateWindow("Hello OpenGL");

    // register the display function, triggered whenever a new 
    // frame is required
    glutDisplayFunc(display);

    // start the event loop: the system will listen for events 
    // and trigger their respective callback functions
    glutMainLoop();

    return (0);
}

// function that draws on the canvas (window in this case)
void display(void)
{
    // set the clear color (more like the color of the rubber)
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

