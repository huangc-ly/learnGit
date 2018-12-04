#include <stdio.h>
#include "Quat.h"
#include <math.h>
#include <Windows.h>
#include "..\..\Include\glut.H"
#include "Camera.h"

Camera g_camera;

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
	UpdateCameraMatrix(&g_camera, );

	// set camera matrix
	glMultMatrixf(g_camera.ViewMatrix.m);
}




int main()
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
#endif

	InitCamera(g_camera, 800, 600, 40, 1.0, 1000.0);



	getchar();
}