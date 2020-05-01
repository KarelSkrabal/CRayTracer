#pragma once

void WriteTitle(int);    // Display title bar information
void ClearScreen(void);
int main();
void BounceProc(void);

struct Vector
{
	float x;
	float y;
	float z;
};

void PrintVector(struct Vector v);
//void PrintVector(const struct Vector * v);
struct Vector ReturnVector(struct Vector*);
void SubstructVectorScalar(struct Vector*, float);
void AddVectorScalar(struct Vector* v, float s);
float Modv(const struct Vector* v);
float ModvCoordinations(float x, float y, float z);
void Normalize(struct Vector* v);
float Dot(const struct Vector* v1, const struct Vector* v2);
struct Vector Plus(const struct Vector* v1, const struct Vector* v2);
struct Vector Minus(const struct Vector* v1, const struct Vector* v2);
struct Vector Cross(const struct Vector* v1, const struct Vector* v2);