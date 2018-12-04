#pragma once
#ifndef QUAT_H_
#define QUAT_H_

#define PIE 3.1415926

// float point 3 element
typedef struct vector3f
{
	vector3f(void)
	{
		x = y = z = 0;
	}

	vector3f(float xi, float yi, float zi)
	{
		x = xi;
		y = yi;
		z = zi;
	}

	void set(float xi, float yi, float zi)
	{
		x = xi;
		y = yi;
		z = zi;
	}

	float x, y, z;
}Vector3F;

typedef struct Quat_t
{
	Quat_t()
	{
		r = 0;
		v.x = v.y = v.z = 0;
	}

	void clear()
	{
		r = 0;
		v.x = v.y = v.z = 0;
	}

	void set(float ri, Vector3F &vi)
	{
		r = ri;
		v = vi;
	}

	float r;
	Vector3F v;
}Quat;


void QUAT_Add(Quat *q1, Quat *q2, Quat *qo);

void QUAT_Sub(Quat *q1, Quat *q2, Quat *qo);

void QUAT_Conjuate(Quat *q, Quat *qo);

void QUAT_Inverse(Quat *q, Quat *qo);

float QUAT_Len(Quat *q);

float QUAT_Len2(Quat *q);

void QUAT_Normalize(Quat *q, Quat *qo);

void QUAT_Mul(Quat *q1, Quat *q2, Quat *qo);

void QUAT_Rotate(Vector3F& axis, float theta, Vector3F &v, Quat &vo);

float VectorDotProduct(Vector3F& v1, Vector3F& v2);
// vector cross product
void VectorCrossProduct(Vector3F& v1, Vector3F& v2, Vector3F& vo);

void VectorAdd(Vector3F& v1, Vector3F& v2, Vector3F& vo);

void VectorSub(Vector3F& v1, Vector3F& v2, Vector3F& vo);

float VectorMagnitude(Vector3F& v);
// normalize vector to unit
void VectorNormalize(Vector3F& v);

void VectorScale(Vector3F& v1, float s, Vector3F& vo);

void VectorInv(Vector3F& v1, Vector3F& vo);


#endif