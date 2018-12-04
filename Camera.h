#ifndef CAMERA_H_
#define CAMERA_H_

#include "Quat.h"

typedef struct camera
{
	float ViewAngleHr;
	float ViewAngleVi;
	float ViewAspect;
	float ViewFrustum[6];
	int Viewport[4];
	int WinWidth;
	int WinHeight;
	
	Vector3F position;
	Vector3F target;
	Vector3F u, v, n;
	
	Matrix16F ViewMatrix;

	camera(){};

}Camera;


void InitCamera(Camera &cam, int nWidth, int nHeight, double fAngleV, double fNear, double fFar);

void UpdateCamera(Camera &cam, Vector3F &pos, Vector3F &att);


#endif