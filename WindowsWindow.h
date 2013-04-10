#pragma once
#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include <Windows.h>
#include <string>
using std::wstring;

#include "AbstractWindow.h"

/**
   Encapsulates a Window's based window
*/
class WindowsWindow : public AbstractWindow
{
protected:
   // The width of the window
	int width; 
   // The height of the window
	int height; 
   // The window's identifier
	HWND hWnd; 
   // Pointer to the window procedure
	WNDPROC WndProcedure;
   // Handle to the window's instance
	HINSTANCE hInstance;

public:
   // Stores the window's title
	wstring title;

public:
   // Constructor
   // Params:
   //   title - the window's title
	WindowsWindow(const wstring& title);
   // Destructor
	virtual ~WindowsWindow(void);
   // Creates the window
	virtual bool create();
   // Shows the window
	void show();
   // Processes the window's events
	virtual void processEvents();
   // Shows a message in a standard message box
	void showMessage(wstring information);

protected:
   // The window procedure
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif

