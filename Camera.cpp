#include "Camera.h"
#include "math.h"


void InitCamera(Camera &cam, int nWidth, int nHeight, double fAngleV, double fNear, double fFar)
{
	// update view port
	cam.Viewport[0] = 0;
	cam.Viewport[1] = 0;
	cam.Viewport[2] = nWidth;
	cam.Viewport[3] = nHeight;
	cam.ViewAspect = float(nWidth) / float(nHeight);
	// update view angle: set vertical angle, compute horizontal angle from vertical angle and view aspect
	cam.ViewAngleVi = fAngleV;
	cam.ViewAngleHr = atan(cam.ViewAspect * tan(fAngleV * PIE / 360.0)) * 360.0 / PIE;

	cam.ViewFrustum[CAMERA_FRUSTUM_F] = fFar;
	cam.ViewFrustum[CAMERA_FRUSTUM_N] = fNear;
	cam.ViewFrustum[CAMERA_FRUSTUM_T] = tan(fAngleV * PIE / 360.0) * fNear;
	cam.ViewFrustum[CAMERA_FRUSTUM_B] = -cam.ViewFrustum[CAMERA_FRUSTUM_T];
	cam.ViewFrustum[CAMERA_FRUSTUM_R] = cam.ViewAspect * cam.ViewFrustum[CAMERA_FRUSTUM_T];
	cam.ViewFrustum[CAMERA_FRUSTUM_L] = -cam.ViewFrustum[CAMERA_FRUSTUM_R];


	cam.position.set(0, 0, 10);
	cam.target.set(0, 0, 0);
	cam.v.set(0, 1, 0); // Up-vector

}