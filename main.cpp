#include <stdio.h>
#include "Quat.h"
#include <math.h>
#include <Windows.h>
#include "glut.H"
#include "Camera.h"

Camera g_camera;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	InitCamera(g_camera, 800, 600, 60, 1, 100);
	glViewport(0, 0, 800, 600);
}


void SVSPreRender(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(g_camera.ViewFrustum[CAMERA_FRUSTUM_L], g_camera.ViewFrustum[CAMERA_FRUSTUM_R],
		g_camera.ViewFrustum[CAMERA_FRUSTUM_B], g_camera.ViewFrustum[CAMERA_FRUSTUM_T],
		g_camera.ViewFrustum[CAMERA_FRUSTUM_N], g_camera.ViewFrustum[CAMERA_FRUSTUM_F]);

	// set view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// update camera matrix
	UpdateCamera(g_camera, Vector3F(0, 0, 50), Vector3F(10, 0, 0));

	// set camera matrix
	glMultMatrixf(g_camera.ViewMatrix.m);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	SVSPreRender();

	glPushMatrix();
	glutWireSphere(1.0, 20, 16);   /* draw sun */

	glPopMatrix();
	glFlush();
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
#if 0
	Quat result;
	QUAT_Rotate(Vector3F(0, 0, 1), PIE / 2.0, Vector3F(0, 1, 0), result);

	printf("r: %f\ta: %f\tb: %f\tc: %f\n", result.r, result.v.x, result.v.y, result.v.z);

	result.clear();
	Vector3F axis(1, 1, 1);
	VectorNormalize(axis);
	QUAT_Rotate(axis, PIE / 2.0, Vector3F(0.707, 0.707, 0), result);

	printf("r: %f\ta: %f\tb: %f\tc: %f\n", result.r, result.v.x, result.v.y, result.v.z);


	InitCamera(g_camera, 800, 600, 40, 1.0, 1000.0);
#endif

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);

	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;

}