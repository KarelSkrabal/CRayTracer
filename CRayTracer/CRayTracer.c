
//#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "Main.h"
//#include <process.h>

HANDLE  hConsoleOut;                 // Handle to the console
HANDLE  hRunMutex;                   // "Keep Running" mutex
HANDLE  hScreenMutex;                // "Screen update" mutex
int     ThreadNr;                    // Number of threads started
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; // Console information
COORD   consoleSize;
BOOL    bTrails;

int main()
{
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	consoleSize.X = csbiInfo.srWindow.Right;
	consoleSize.Y = csbiInfo.srWindow.Bottom;
	ClearScreen();
	WriteTitle(0);
	BounceProc(/*void* pMyID*/);
	//
	struct Vector v,vv, rr;
	v.x = 1.0;
	v.y = 1.0;
	v.z = 1.0;
	vv.x = 2.0;
	vv.y = 2.0;
	vv.z = 2.0;
	
	printf("%f %f %f", v.x, v.y, v.z);
	struct Vector *pVector;
	//pVector = &v;

	struct Vector rrr = Plus(&v, &vv);
	struct Vector r = Minus(&v, &vv);
	//AddVectorScalar(pVector, 2);
	pVector = &v;
	Normalize(pVector);
	printf("%f %f %f", pVector->x, pVector->y, pVector->z);
	PrintVector(v);
	PrintVector(*pVector);
	ReturnVector(pVector);
	v = *pVector;
	PrintVector(v);
	v.x += 2.0;
	v.y += 2.0;
	v.z += 2.0;
	printf("\nmagnitude = %f", Modv(&v));
	PrintVector(v);
	SubstructVectorScalar(pVector, 10);
	PrintVector(*pVector);
	AddVectorScalar(pVector, 1);
	PrintVector(*pVector);
}

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

void PrintVector(const struct Vector v)
{
	printf("\n%f %f %f", v.x, v.y, v.z);
}

struct Vector ReturnVector(struct Vector* v)
{
	v->x += 10.0;
	v->y += 10.0;
	v->z += 10.0;
	return *v;
}

void BounceProc(/*void* pMyID*/)
{
	wchar_t MyCell, OldCell;
	WORD    MyAttrib, OldAttrib = 0;
	wchar_t BlankCell = 0x20;
	COORD   Coords, Delta;
	COORD   Old = { 0,0 };
	DWORD   Dummy;
	//char* MyID = (char*)pMyID;

	// Generate update increments and initial
	// display coordinates.
	//srand((unsigned int)* MyID * 3);

	Coords.X = /*getrandom(0, consoleSize.X - 1)*/ 50;
	Coords.Y = /*getrandom(0, consoleSize.Y - 1)*/ 10;
	Delta.X = /*getrandom(-3, 3)*/-3;
	Delta.Y = /*getrandom(-3, 3)*/-3;

	// Set up character & generate color
	// attribute from thread number.
	//if (*MyID > 16)
		//MyCell = 0x60 + 56/**MyID*/ - 16; // lower case
	MyCell = 46;
	//else
		//MyCell = 0x40 + *MyID;      // upper case
	MyAttrib = /**MyID*/30 & 0x0f;   // force black background
	//MyAttrib = 30;

	//test
	for (int i = 0; i < 20; i++) {
		for (int y = 0; y < 20; y++) {
			MyAttrib = /**MyID*/(30 + i) & 0x0f;   // force black background
			Coords.X = /*getrandom(0, consoleSize.X - 1)*/ 50 + i;
			Coords.Y = /*getrandom(0, consoleSize.Y - 1)*/ 10 + y;
			WriteConsoleOutputCharacterW(hConsoleOut, &MyCell, 1,
										 Coords, &Dummy);
			WriteConsoleOutputAttribute(hConsoleOut, &MyAttrib, 1,
										Coords, &Dummy);
		}

	}

	//test

	//do
	//{
	//	// Wait for display to be available, then lock it.
	//	WaitForSingleObject(hScreenMutex, INFINITE);

	//	if (!bTrails)
	//	{
	//		// If we still occupy the old screen position, blank it out.
	//		ReadConsoleOutputCharacterW(hConsoleOut, &OldCell, 1,
	//									Old, &Dummy);
	//		ReadConsoleOutputAttribute(hConsoleOut, &OldAttrib, 1,
	//								   Old, &Dummy);
	//		if ((OldCell == MyCell) && (OldAttrib == MyAttrib))
	//			WriteConsoleOutputCharacterW(hConsoleOut, &BlankCell, 1,
	//										 Old, &Dummy);
	//	}

	//	// Draw new character, then clear screen lock
	//	WriteConsoleOutputCharacterW(hConsoleOut, &MyCell, 1,
	//								 Coords, &Dummy);
	//	WriteConsoleOutputAttribute(hConsoleOut, &MyAttrib, 1,
	//								Coords, &Dummy);
	//	ReleaseMutex(hScreenMutex);

	//	// Increment the coordinates for next placement of the block.
	//	Old.X = Coords.X;
	//	Old.Y = Coords.Y;
	//	Coords.X += Delta.X;
	//	Coords.Y += Delta.Y;

	//	// If we are about to go off the screen, reverse direction
	//	if (Coords.X < 0 || Coords.X >= consoleSize.X)
	//	{
	//		Delta.X = -Delta.X;
	//		Beep(400, 50);
	//	}
	//	if (Coords.Y < 0 || Coords.Y > consoleSize.Y)
	//	{
	//		Delta.Y = -Delta.Y;
	//		Beep(600, 50);
	//	}
	//}
	//// Repeat while RunMutex is still taken.
	//while (WaitForSingleObject(hRunMutex, 75L) == WAIT_TIMEOUT);
}


void WriteTitle(int ThreadNum)
{
	enum
	{
		sizeOfNThreadMsg = 120
	};
	wchar_t NThreadMsg[sizeOfNThreadMsg] = { L"ahoj" };

	swprintf_s(NThreadMsg, sizeOfNThreadMsg,
			   L"Threads running: %02d.  Press 'A' "
			   L"to start a thread, 'T' to toggle "
			   L"trails, 'Q' to quit.", ThreadNum);
	SetConsoleTitleW(NThreadMsg);
}

void ClearScreen(void)
{
	DWORD    dummy = 0;
	COORD    Home = { 0, 0 };
	FillConsoleOutputCharacterW(hConsoleOut, L' ', consoleSize.X * consoleSize.Y, Home, &dummy);
}
