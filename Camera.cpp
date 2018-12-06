#include "Camera.h"
#include "math.h"
#include "Quat.h"

#define DEG2RAD (PIE/180)

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

void CalcUVN(Camera &cam, Vector3F &att)
{
	float Y = sin(att.x * DEG2RAD); // att.x£ºpitch
	float X = cos(att.x * DEG2RAD) * sin(att.z * DEG2RAD); // att.z: yaw
	float Z = cos(att.x * DEG2RAD) * cos(att.z * DEG2RAD);

	cam.n.set(X, Y, Z);
	float len = VectorMagnitude(cam.n);
	cam.n.set(X / len, Y / len, Z / len);
	VectorCrossProduct(cam.n, cam.v, cam.u);
	VectorCrossProduct(cam.n, cam.u, cam.v);
}

void SetViewMatrix(Camera &cam)
{
	cam.ViewMatrix.m[0] = cam.u.x;
	cam.ViewMatrix.m[1] = cam.v.x;
	cam.ViewMatrix.m[2] = cam.n.x;
	cam.ViewMatrix.m[3] = 0;
	cam.ViewMatrix.m[4] = cam.u.y;
	cam.ViewMatrix.m[5] = cam.v.y;
	cam.ViewMatrix.m[6] = cam.n.y;
	cam.ViewMatrix.m[7] = 0;
	cam.ViewMatrix.m[8] = cam.u.z;
	cam.ViewMatrix.m[9] = cam.v.z;
	cam.ViewMatrix.m[10] = cam.n.z;
	cam.ViewMatrix.m[11] = 0;
	cam.ViewMatrix.m[12] = -VectorDotProduct(cam.u, cam.position);
	cam.ViewMatrix.m[13] = -VectorDotProduct(cam.v, cam.position);
	cam.ViewMatrix.m[14] = -VectorDotProduct(cam.n, cam.position);
	cam.ViewMatrix.m[15] = 1;
}

void UpdateCamera(Camera &cam, Vector3F &pos, Vector3F &att)
{
	cam.position.set(pos.x, pos.y, pos.z);
	CalcUVN(cam, att);
	SetViewMatrix(cam);
}

void UpdateFrustum()
{

}