#ifndef vector_H_
#define vector_H_
struct Vector
{
	float x;
	float y;
	float z;
};

struct Vector Plus(const struct Vector* v1, const struct Vector* v2);
#endif
