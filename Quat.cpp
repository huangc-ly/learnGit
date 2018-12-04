#include "Quat.h"
#include <math.h>

float VectorDotProduct(Vector3F& v1, Vector3F& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// vector cross product
inline void VectorCrossProduct(Vector3F& v1, Vector3F& v2, Vector3F& vo)
{
	vo.x = ((v1.y * v2.z) - (v1.z * v2.y));
	vo.y = ((v1.z * v2.x) - (v1.x * v2.z));
	vo.z = ((v1.x * v2.y) - (v1.y * v2.x));
}


void VectorAdd(Vector3F& v1, Vector3F& v2, Vector3F& vo)
{
	vo.x = v1.x + v2.x;
	vo.y = v1.y + v2.y;
	vo.z = v1.z + v2.z;
}

void VectorSub(Vector3F& v1, Vector3F& v2, Vector3F& vo)
{
	vo.x = v1.x - v2.x;
	vo.y = v1.y - v2.y;
	vo.z = v1.z - v2.z;
}

float VectorMagnitude(Vector3F& v)
{
	return (float)sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

float VectorMagnitude2(Vector3F& v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

void VectorNormalize(Vector3F& v)
{
	float mag = VectorMagnitude(v);
	if (mag > 1.0e-8f)
	{
		v.x = v.x / mag;
		v.y = v.y / mag;
		v.z = v.z / mag;
	}
}

void VectorScale(Vector3F& v1, float s, Vector3F& vo)
{
	vo.x = v1.x * s;
	vo.y = v1.y * s;
	vo.z = v1.z * s;
}

void VectorZero(Vector3F& v)
{
	v.x = v.y = v.z = 0;
}


void VectorInv(Vector3F& v1, Vector3F& vo)
{
	vo.x = -v1.x;
	vo.y = -v1.y;
	vo.z = -v1.z;
}

void QUAT_Add(Quat *q1, Quat *q2, Quat *qo)
{
	qo->r = q1->r + q2->r;
	VectorAdd(q1->v, q2->v, qo->v);
}

void QUAT_Sub(Quat *q1, Quat *q2, Quat *qo)
{
	qo->r = q1->r - q2->r;
	VectorSub(q1->v, q2->v, qo->v);
}

void QUAT_Conjuate(Quat *q, Quat *qo)
{
	qo->r = q->r;
	VectorInv(q->v, qo->v);
}

void QUAT_Inverse(Quat *q, Quat *qo)
{
	float len = QUAT_Len2(q);
	if (len > 1.0e-8f)
	{
		float col = 1.0 / len;
		qo->r = q->r * col;
		VectorScale(q->v, col, qo->v);
	}
}

float QUAT_Len(Quat *q)
{
	return sqrtf(VectorMagnitude2(q->v) + q->r * q->r);
}

float QUAT_Len2(Quat *q)
{
	return (VectorMagnitude2(q->v) + q->r * q->r);
}

void QUAT_Normalize(Quat *q, Quat *qo)
{
	float len = QUAT_Len(q);
	if (len > 1.0e-8f)
	{
		float col = 1.0 / len;
		qo->r = q->r * col;
		VectorScale(q->v, col, qo->v);
	}
}

void QUAT_Mul(Quat *q1, Quat *q2, Quat *qo)// q1*q2
{
	qo->r = q1->r * q2->r - VectorDotProduct(q1->v, q2->v);
	Vector3F temp1, temp2, temp3;
	VectorScale(q2->v, q1->r, temp1);
	VectorScale(q1->v, q2->r, temp2);
	VectorCrossProduct(q1->v, q2->v, temp3);
	VectorAdd(temp1, temp2, temp1);
	VectorAdd(temp1, temp3, qo->v);
}

void QUAT_Rotate(Vector3F& axis, float theta, Vector3F &v, Quat &vo)
{
	Quat a, b, b_conj, result;
	Vector3F temp;
	VectorScale(axis, sin(theta / 2.0), temp);
	a.set(0, v);
	b.set(cos(theta / 2.0), temp);
	QUAT_Conjuate(&b, &b_conj);
	QUAT_Triple_Mul(&b, &a, &b_conj, &vo);
}

void QUAT_Scale(Quat *q, float scale)
{
	q->r *= scale;
	VectorScale(q->v, scale, q->v);
}


void QUAT_Triple_Mul(Quat *q1, Quat *q2, Quat *q3, Quat *qo)
{
	Quat tmp;
	QUAT_Mul(q1, q2, &tmp);
	QUAT_Mul(&tmp, q3, qo);
}