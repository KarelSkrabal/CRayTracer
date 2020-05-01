#include "Vector.h"
#include <math.h>

struct Vector Plus(const struct Vector* v1, const struct Vector* v2)
{
	struct Vector v;
	v.x = v1->x + v2->x;
	v.y = v1->y + v2->y;
	v.z = v1->z + v2->z;
	return v;
}

struct Vector Minus(const struct Vector* v1, const struct Vector* v2)
{
	struct Vector v;
	v.x = v1->x - v2->x;
	v.y = v1->y - v2->y;
	v.z = v1->z - v2->z;
	return v;
}

float Dot(const struct Vector* v1, const struct Vector* v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

struct Vector Cross(const struct Vector* v1, const struct Vector* v2)
{
	struct Vector v;
	v.x = v1->y * v2->z - v2->y * v1->z;
	v.y = (v1->x * v2->z - v2->x * v1->z) * -1;
	v.z = v1->x * v2->y - v2->x * v1->y;
	return v;
}

float GetCosAngle(const struct Vector* v1, const struct Vector* v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z) / (ModvCoordinations(v1->x, v1->y, v1->z) * ModvCoordinations(v2->x, v2->y, v2->z));
}

void Normalize(struct Vector* v)
{
	float length = Modv(v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

float ModvCoordinations(float x, float y, float z)
{
	return sqrtf(x * x + y * y + z * z);
}

float Modv(const struct Vector* v)
{
	return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

void SubstructVectorScalar(struct Vector* v, float s)
{
	v->x -= s;
	v->y -= s;
	v->z -= s;
}

void AddVectorScalar(struct Vector* v, float s)
{
	v->x += s;
	v->y += s;
	v->z += s;
}

//void PrintVector(const struct Vector v)
//{
//	printf("\n%f %f %f", v.x, v.y, v.z);
//}

struct Vector ReturnVector(struct Vector* v)
{
	v->x += 10.0;
	v->y += 10.0;
	v->z += 10.0;
	return *v;
}