#include "main.h"

using namespace std;

static int year = 0, day = 0, yearMoon = 0;
static bool pos = 0;



Camera Cam;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	SetCursorPos(GLUT_WINDOW_WIDTH / 2, GLUT_WINDOW_HEIGHT / 2);
	
	Cam.Position_Camera(0.0, 0.0, 5.0,    0.0, 0.0, 0.0,     0.0, 1.0, 0.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	Cam.Mouse_Move(GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Cam.mPos.x,  Cam.mPos.y,  Cam.mPos.z,
			  Cam.mView.x, Cam.mView.y, Cam.mView.z,
			  Cam.mUp.x,   Cam.mUp.y,   Cam.mUp.z);
	
	glPushMatrix();
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
		glutWireSphere(1.0, 20, 16);   /* draw sun */
	glPopMatrix();
	glPushMatrix();
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
		glTranslatef(2.0, 0.0, 0.0);
		glPushMatrix();
			glRotatef((GLfloat)yearMoon, 0.0, 1.0, 0.0);
			glTranslatef(0.5, 0.0, 0.0);
			glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
			glutWireSphere(0.05, 10, 8);//draw moon
		glPopMatrix();
		glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
		glutWireSphere(0.2, 10, 8);    /* draw smaller planet */
	glPopMatrix();
	glPushMatrix();
	Draw_Grid();
	glPopMatrix();
	glutSwapBuffers();

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.0, 20);
	
}

void animation(int t) 
{
	day = (day + 5) % 360;
	year = (year + 1) % 360;
	yearMoon = (yearMoon + 10) % 360;
	glutPostRedisplay();
	glutTimerFunc(20, animation, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'w':
			Cam.Move_Camera_Forward(CAMERASPEED);
			break;
		case 's':
			Cam.Move_Camera_Forward(-CAMERASPEED);
			break;
		case 'd':
			Cam.Move_Camera_Side(CAMERASPEED);
			break;
		case 'a':
			Cam.Move_Camera_Side(-CAMERASPEED);
			break;
		case 27:
			glutLeaveMainLoop();
			break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && state == GLUT_DOWN) 
		arc = true;
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(20, animation, 0);
	glutMainLoop();
	return 0;
}

void Draw_Grid()
{
	for (int i = -400; i <= 400; i += 10)
	{
		glBegin(GL_LINES);
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-500, -20, i);
		glVertex3f(500, -20, i);
		glVertex3f(i, -20, -500);
		glVertex3f(i, -20, 500);
		glEnd();
	}
}