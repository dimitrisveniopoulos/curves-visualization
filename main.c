#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>

int question = 1;
int controlPoints = 0;
GLfloat p[7][3];
int edited = 0;
float distance = 10;
int nearestPointIndex;
float initial_x;
float initial_y;
float camera_left_right = 0;
float camera_up_down = 0;
static double M[4][4] = {{1,0,0,0},
                         {-0.833333,3, -1.5, 0.333333},
                         {0.333333,-1.5,3,-0.833333},
                         {0,0,0,1}};

void initialize()
{
    glEnable(GL_MAP1_VERTEX_3);
    glEnable(GL_MAP2_VERTEX_3);
    glClearColor(0, 0, 0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-600, 600,-200 , 600,-1500,1500);
    glMatrixMode(GL_MODELVIEW);
}

float calculateDistance(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void question1()
{
    if (controlPoints == 7)
    {
        GLfloat q[7][3];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                q[i][j] = 0;
                q[i + 3][j] = 0;
                for (int k = 0; k < 4; k++)
                {
                    q[i][j] += M[i][k] * p[k][j];
                    q[i + 3][j] += M[i][k] * p[k + 3][j];
                }
            }
        }

        glColor3f(1.0,1.0,0.0);
        glMap1f(GL_MAP1_VERTEX_3,0,1,3,4,&q[0][0]);
        glMapGrid1f(100,0,1);
        glEvalMesh1(GL_LINE,0,100);

        glColor3f(1.0,1.0,1.0);
        glMap1f(GL_MAP1_VERTEX_3,0,1,3,4,&q[3][0]);
        glMapGrid1f(100,0,1);
        glEvalMesh1(GL_LINE,0,100);
    }
    if (controlPoints <= 7)
    {
        for (int i = 0; i < controlPoints; i++)
        {
            if (i < 3)
                glColor3f(1.0,0.0,0.0);
            else if (i == 3)
                glColor3f(0.0,0.0,1.0);
            else
                glColor3f(0.0,1.0,0.0);
            glBegin(GL_POLYGON);
            glVertex2f(p[i][0] - 2, p[i][1] + 2);
            glVertex2f(p[i][0] + 2, p[i][1] + 2);
            glVertex2f(p[i][0] + 2, p[i][1] - 2);
            glVertex2f(p[i][0] - 2, p[i][1] - 2);
            glEnd();
        }
    }
}

void question2()
{
    if (controlPoints == 6)
    {
        glColor3f(1.0,1.0,0.0);
        glMap1f(GL_MAP1_VERTEX_3,0,1,3,7,&p[0][0]);
        glMapGrid1f(100,0,1);
        glEvalMesh1(GL_LINE,0,100);
    }

    glColor3f(1.0,0.0,0.0);
    for (int i = 0; i < controlPoints; i++)
    {
        glBegin(GL_POLYGON);
        glVertex2f(p[i][0] - 2, p[i][1] + 2);
        glVertex2f(p[i][0] + 2, p[i][1] + 2);
        glVertex2f(p[i][0] + 2, p[i][1] - 2);
        glVertex2f(p[i][0] - 2, p[i][1] - 2);
        glEnd();
    }
}

void question3()
{
    if (edited == 0)
    {
        p[0][0] = -300, p[0][1] = 200, p[0][2] = 0;
        p[1][0] = -200, p[1][1] = 300, p[1][2] = 0;
        p[2][0] = -100, p[2][1] = 330, p[2][2] = 0;
        p[3][0] =    0, p[3][1] = 250, p[3][2] = 0;
        p[4][0] =  100, p[4][1] = 170, p[4][2] = 0;
        p[5][0] =  200, p[5][1] = 300, p[5][2] = 0;
        p[6][0] =  300, p[6][1] = 320, p[6][2] = 0;
    }

    glColor3f(1.0,1.0,0.0);
    glMap1f(GL_MAP1_VERTEX_3,0,1,3,4,&p[0][0]);
    glMapGrid1f(100,0,1);
    glEvalMesh1(GL_LINE,0,100);

    glColor3f(1.0,1.0,1.0);
    glMap1f(GL_MAP1_VERTEX_3,0,1,3,4,&p[3][0]);
    glMapGrid1f(100,0,1);
    glEvalMesh1(GL_LINE,0,100);

    for (int i = 0; i < 7; i++)
    {
        if (i < 3)
            glColor3f(1.0,0.0,0.0);
        else if (i == 3)
            glColor3f(0.0,0.0,1.0);
        else
            glColor3f(0.0,1.0,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(p[i][0] - 2, p[i][1] + 2);
        glVertex2f(p[i][0] + 2, p[i][1] + 2);
        glVertex2f(p[i][0] + 2, p[i][1] - 2);
        glVertex2f(p[i][0] - 2, p[i][1] - 2);
        glEnd();
    }

}

void question4()
{
    glLoadIdentity();
    glRotatef(camera_left_right, 0, 1, 0);
    glRotatef(camera_up_down,1,0,0);

    GLfloat points[4][4][3] = {{{0,   200, 200},{100, 100, 100},{100, 100, 400},{0,   200, 300}},
                               { {100, 200, 200},{200, 100, 100},{200, 100, 400},{100, 200, 300}},
                               {{100, 300, 200},{200, 400, 100},{200, 400, 400},{100,300,300}},
                               {{0,300,200},{100,400,100},{100,400,400},{0,300,300}}};

    GLfloat bezier[4][4][3];
    for (int x = 0; x < 4; x++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                bezier[x][i][j] = 0;
                for (int k = 0; k < 4; k++)
                {
                    bezier[x][i][j] += M[i][k] * points[x][k][j];
                }
            }
        }
    }
    glColor3f(1.0,1.0,0.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0,1,12, 4, &bezier[0][0][0]);
    glMapGrid2f(100,0,1,100,0,1);
    glEvalMesh2(GL_LINE,0,100,0,100);

    glColor3f(1.0,0.0,0.0);
    for (int i =0; i < 4; i ++)
    {
        for (int j=0; j < 4 ; j ++)
        {
            glBegin(GL_POLYGON);
            glVertex3f(points[i][j][0] - 2, points[i][j][1] + 2, points[i][j][2]);
            glVertex3f(points[i][j][0] + 2, points[i][j][1] + 2, points[i][j][2]);
            glVertex3f(points[i][j][0] + 2, points[i][j][1] - 2, points[i][j][2]);
            glVertex3f(points[i][j][0] - 2, points[i][j][1] - 2, points[i][j][2]);
            glEnd();
        }
    }

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (question == 1)
        question1();
    else if (question == 2)
        question2();
    else if (question == 3)
        question3();
    else if (question == 4)
        question4();

    glFlush();
    glutSwapBuffers();
}

void menu(int id){

    if (id == 1)
    {
        question = 1;
        controlPoints = 0;
    }
    if (id == 2)
    {
        question = 2;
        controlPoints = 0;
    }
    if (id == 3)
    {
        question = 3;
        edited = 0;
    }
    if (id == 4)
    {
        question = 4;
        camera_up_down = 0;
        camera_left_right = 0;
    }
    if (id == 5)
        exit(0);

    display();
}

//Rotate camera
void keyboard(int key, int x, int y){
    if (key == GLUT_KEY_LEFT)
        camera_left_right += 1;
    else if (key == GLUT_KEY_RIGHT)
        camera_left_right -= 1;
    else if (key == GLUT_KEY_DOWN)
        camera_up_down -= 1;
    else if (key == GLUT_KEY_UP)
        camera_up_down += 1;
    display();
}

void mouseCallback(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (question == 1)
        {
            //Create control points based on mouse input
            if (controlPoints < 7)
            {
                p[controlPoints][0] = x - 600;
                p[controlPoints][1] = 600 - y;
                p[controlPoints][2] = 0;
                controlPoints++;
            }
            display();
        }
        else if (question == 2)
        {
            //Create control points based on mouse input
            if (controlPoints < 6)
            {
                p[controlPoints][0] = x - 600;
                p[controlPoints][1] = 600 - y;
                p[controlPoints][2] = 0;
                controlPoints++;
            }
            if (controlPoints == 6)
            {
                p[controlPoints][0] = p[0][0];
                p[controlPoints][1] = p[0][1];
                p[controlPoints][2] = 0;
            }
            display();
        }

        initial_x = x;
        initial_y = y;

        //Find the nearest control point
        nearestPointIndex = -1;
        float min = distance;
        for (int i = 0; i < 7; i ++)
        {
            float d = calculateDistance(x - 600, 600 - y, p[i][0], p[i][1]);
            if (d < min)
            {
                min = d;
                nearestPointIndex = i;
            }
        }
    }
}

void motionCallback(int x, int y)
{
    //Move control point
    if (nearestPointIndex != -1){
        p[nearestPointIndex][0] += (x - initial_x);
        p[nearestPointIndex][1] -= (y - initial_y);
        if (question == 2)
        {
            if (nearestPointIndex == 0)
            {
                p[6][0] += (x - initial_x);
                p[6][1] -= (y - initial_y);
            }
        }
        else if (question == 3)
        {
            edited = 1;
            if (nearestPointIndex == 2)
            {
                p[4][0] -= (x - initial_x);
                p[4][1] += (y - initial_y);
            }
            else if (nearestPointIndex == 4)
            {
                p[2][0] -= (x - initial_x);
                p[2][1] += (y - initial_y);
            }
            else if (nearestPointIndex == 3)
            {
                p[2][0] += (x - initial_x);
                p[2][1] -= (y - initial_y);
                p[4][0] += (x - initial_x);
                p[4][1] -= (y - initial_y);
            }
        }
        initial_x = x;
        initial_y = y;
        display();
    }
}

int main(int argc, char** argv) {

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(1200,800);
    glutInitWindowPosition(400,100);
    glutCreateWindow("Curves Visualisation");
    glutDisplayFunc(display);
    initialize();
    display();
    glutSwapBuffers();

    glutCreateMenu(menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutAddMenuEntry("2 Cubic Interpolation Curves", 1);
    glutAddMenuEntry("6th Degree Bezier", 2);
    glutAddMenuEntry("2 Bezier Curves", 3);
    glutAddMenuEntry("Bicubic Surface", 4);
    glutAddMenuEntry("Quit", 5);

    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
    glutSpecialFunc(keyboard);

    glutMainLoop();

    return 0;
}