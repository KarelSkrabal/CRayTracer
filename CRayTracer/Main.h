#pragma once

void WriteTitle(int);    // Display title bar information
void ClearScreen(void);
int main();
void BounceProc(void);

#ifndef vector_H_
#define vector_H_
struct Vector
{
	float x;
	float y;
	float z;
};
#endif

#ifndef color_H_
#define color_H_
struct Color
{
	unsigned char x;
	unsigned char y;
	unsigned char z;
};
#endif

void PrintVector(struct Vector v);
//void PrintVector(const struct Vector * v);
struct Vector ReturnVector(struct Vector*);
void SubstructVectorScalar(struct Vector*, float);
void AddVectorScalar(struct Vector* v, float s);
float Modv(const struct Vector* v);
float ModvCoordinations(float x, float y, float z);
void Normalize(struct Vector* v);
float Dot(const struct Vector* v1, const struct Vector* v2);
struct Vector Cross(const struct Vector* v1, const struct Vector* v2);
struct Vector Plus(const struct Vector* v1, const struct Vector* v2);
struct Vector Minus(const struct Vector* v1, const struct Vector* v2);
struct Vector Cross(const struct Vector* v1, const struct Vector* v2);
float GetCosAngle(const struct Vector* v1, const struct Vector* v2);