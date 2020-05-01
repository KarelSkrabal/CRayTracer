
//#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "Main.h"
#include "Vector.h"

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
	struct Vector v;
	struct Vector v1,v2;
	v1.x = 1;
	v1.y = 1;
	v1.z = 1;
	v2.x = 1;
	v2.y = 1;
	v2.z = 1;
	float dot = Dot(&v1, &v2);
	//
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
