#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers.
#endif

#include <Windows.h>
#include "Renderer.h"
#include "GameLogic.h"

// Handle to the window
extern HWND hwnd;

// name of the window (not the title)
extern LPCTSTR WindowName;

// title of the window
extern LPCTSTR WindowTitle;

// width and height of the window
extern int Width;
extern int Height;

// is window full screen?
extern bool FullScreen;

// create a window
bool InitializeWindow(HINSTANCE hInstance,
	int ShowWnd,
	bool fullscreen);

// callback function for windows messages
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

void WaitForPreviousFrame(); // wait until gpu is finished with command list
