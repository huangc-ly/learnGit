#include <stdio.h>
#include "Quat.h"
#include <math.h>

int main()
{
	Quat result;
	QUAT_Rotate(Vector3F(0, 0, 1), PIE / 2.0, Vector3F(0, 1, 0), result);

	printf("r: %f\ta: %f\tb: %f\tc: %f\n", result.r, result.v.x, result.v.y, result.v.z);

	result.clear();
	QUAT_Rotate(Vector3F(0, 1, 0), PIE / 2.0, Vector3F(0.707, 0.707, 0), result);

	printf("r: %f\ta: %f\tb: %f\tc: %f\n", result.r, result.v.x, result.v.y, result.v.z);



	getchar();
}