#include "Vector.h"
#include "Color.h"

#ifndef object_H_
#define object_H_
struct Object
{
	struct Vector position;
	struct Color color;
	float radius;
};
#endif
