#pragma once
#ifndef QUAT_H_
#define QUAT_H_

#define PIE 3.1415926
#define CAMERA_FRUSTUM_L 0
#define CAMERA_FRUSTUM_R 1
#define CAMERA_FRUSTUM_B 2
#define CAMERA_FRUSTUM_T 3
#define CAMERA_FRUSTUM_N 4
#define CAMERA_FRUSTUM_F 5


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

void QUAT_Triple_Mul(Quat *q1, Quat *q2, Quat *q3, Quat *qo);

void QUAT_Rotate(Vector3F& axis, float theta, Vector3F &v, Quat &vo);

void QUAT_Scale(Quat *q, float scale);

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


// float matrix 16 element
typedef struct matrix16f
{
	matrix16f(void)
	{
		for (int i = 0; i<16; i++) { m[i] = 0.0f; }
		m[0] = m[5] = m[10] = m[15] = 1.0f;
	}

	float m[16];

	void Identity(void)
	{
		for (int i = 0; i<16; i++) { m[i] = 0.0f; }
		m[0] = m[5] = m[10] = m[15] = 1.0f;
	}

	void Transform(const Vector3F& vIn, Vector3F& vOut)
	{
		vOut.x = m[0] * vIn.x + m[4] * vIn.y + m[8] * vIn.z + m[12];
		vOut.y = m[1] * vIn.x + m[5] * vIn.y + m[9] * vIn.z + m[13];
		vOut.z = m[2] * vIn.x + m[6] * vIn.y + m[10] * vIn.z + m[14];
	}

	void Multiply(const matrix16f& M)
	{
		float C[16] = { 0 };

		for (int i = 0; i<4; i++)
		{
			for (int j = 0; j<4; j++)
			{
				C[j * 4 + i] = 0.0f;
				for (int k = 0; k<4; k++)
				{
					C[j * 4 + i] += m[k * 4 + i] * M.m[j * 4 + k];
				}
			}
		}

		for (int i = 0; i<16; i++) { m[i] = C[i]; }
	}
}Matrix16F;



#endif