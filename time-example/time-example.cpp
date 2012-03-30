// time-example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>
#include <iostream>
#include <sstream>

//------------------------------------------------------------------------
//Input Simulation Section
//------------------------------------------------------------------------
//The following classes are for creating mouse input event simulation in windows. 
//They require Windows.h be included.
//Credit for them goes to: golanshahar of http://forums.codeguru.com/showthread.php?t=377394
//He is awesome.
void MouseMove (int x, int y )
{  
  double fScreenWidth    = ::GetSystemMetrics( SM_CXSCREEN )-1; 
  double fScreenHeight  = ::GetSystemMetrics( SM_CYSCREEN )-1; 
  double fx = x*(65535.0f/fScreenWidth);
  double fy = y*(65535.0f/fScreenHeight);
  INPUT  Input={0};
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
  Input.mi.dx = fx;
  Input.mi.dy = fy;
  ::SendInput(1,&Input,sizeof(INPUT));
}

void LeftClick ( )
{  
  INPUT    Input={0};
  // left down 
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
  ::SendInput(1,&Input,sizeof(INPUT));

  // left up
  ::ZeroMemory(&Input,sizeof(INPUT));
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
  ::SendInput(1,&Input,sizeof(INPUT));
}

void RightClick ( )
{  
  INPUT    Input={0};
  // right down 
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_RIGHTDOWN;
  ::SendInput(1,&Input,sizeof(INPUT));

  // right up
  ::ZeroMemory(&Input,sizeof(INPUT));
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_RIGHTUP;
  ::SendInput(1,&Input,sizeof(INPUT));
}
//------------------------------------------------------------------------
//End Input Simulation Section
//------------------------------------------------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
	//Instantiate our time object, which holds the current time.  
	timedll::Time mTime;

	//Update the time held in our time object.  
	mTime.UpdateTime();

	std::cout << "Current UTC time is: ";

	//Print out each of the characters in our time objects time container.
	for(int i = 0; i < mTime.mDataSize; i++)
	{
		std::cout << mTime.mData[i];
	}

	std::cout << "\nInput desired UTC start time in format HOUR:MINUTE:SECOND: ";

	//Get the hour minute and second from the user's input.
	int hour, minute, second;

	scanf( "%d:%d:%d", &hour, &minute, &second );

	//Update the time in our object again.  
	mTime.UpdateTime();

	std::stringstream sstream;

	//Put the data into a stringstream so that we can pull it out formatted later.  
	for(int i = 0; i < mTime.mDataSize; i++)
	{
		sstream << mTime.mData[i];
	}

	//Get the formatted hour minute and second of the clock time.
	int chour, cminute, csecond;

	sstream >> chour >> cminute >> csecond;

	//Calculate how long we have to wait.  
	int whour, wminute, wsecond;

	whour = hour - chour;
	wminute = minute - cminute;
	wsecond = second - csecond;

	int wmilliseconds = (whour * 60 * 60 * 1000) + (wminute * 60 * 1000) + (wsecond * 1000);

	//Wait until the appropriate time.  
	Sleep(wmilliseconds);
	
	//Move the mouse to the center of the screen.
	double fScreenWidth    = ::GetSystemMetrics( SM_CXSCREEN )-1; 
	double fScreenHeight  = ::GetSystemMetrics( SM_CYSCREEN )-1; 
	MouseMove(fScreenWidth/2, fScreenHeight/2);

	//Click the screen.
	LeftClick();

	//Exit the program.
	return 0;
}