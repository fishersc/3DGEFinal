#include "WindowsWindow.h"

#ifndef WINDOWS_OGL_WINDOW_H
#include "WindowsOGLWindow.h"
#endif

WindowsWindow::WindowsWindow(const wstring& title)
{
	width = 500;
	height = 500;
	hWnd = NULL;
	this->title = title;
	WndProcedure = WndProc;
	this->hInstance = NULL;
}

WindowsWindow::~WindowsWindow(void)
{
}

bool WindowsWindow::create()
{
	hInstance = GetModuleHandle(NULL);

	if(hInstance == 0) return false;

	WNDCLASS windowClass;
	windowClass.style = CS_HREDRAW | // Redraw the entire window if a movement or size adjustment changes the width of the client area
		                CS_VREDRAW | // Redraw the entire window if a movement or size adjustment changes the height of the client area
						CS_OWNDC;    // Allocate a unique device context for each window
	windowClass.lpfnWndProc = (WNDPROC) WndProcedure; // Set the window procedure
	windowClass.cbClsExtra = 0; // There are no extra bytes allocated after the window-class structure.
	windowClass.cbWndExtra = 0; // There are no extra bytes allocated after the window instance.
	windowClass.hInstance = hInstance; // Handle to the instance that contains the window procedure for the class
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);   // Handle to the class' icon
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // handle to the class' cursor
	windowClass.hbrBackground = NULL;  // There is no background brush
	windowClass.lpszMenuName = NULL;   // There is no menu
	windowClass.lpszClassName = title.c_str(); // The window class name

	if (!RegisterClass(&windowClass)) return false;

	// Creates an overlapped window with an extended window style
	hWnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, // Forces a top-level window onto the taskbar when the window is visible, the window has a border with a raised edge.
		title.c_str(), // The window class name as defined above
		title.c_str(), // The window name, this is displayed in the title bar
		WS_OVERLAPPEDWINDOW, // An overlapped window
		CW_USEDEFAULT, 0, width, height, // Initial position and size of the window
		NULL, // Handle to the parent window
		NULL, // Handle to the menu
		hInstance, // Handle to the module associated with this window
		NULL // Pointer to the value to be passed to the window
	);

	if(hWnd == NULL) return false;

	return true;
}

void WindowsWindow::processEvents()
{
	// Should be overridden
}

LRESULT CALLBACK WindowsWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
   case WM_SYSCOMMAND: // System commands
      // Check system calls
		switch (wParam){
			case SC_SCREENSAVE:   // Screensaver trying to start?
			case SC_MONITORPOWER: // Monitor trying to enter powersave?
			return 0;				 // Prevent from happening
		}
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void WindowsWindow::show()
{
	if(hWnd != NULL){
		// Activate the window and display it in its current size and position
		ShowWindow(hWnd, SW_MAXIMIZE); 
		// Update the client area by sending the WM_PAINT message
		UpdateWindow(hWnd);
	}
}

void WindowsWindow::showMessage(wstring information)
{
	MessageBox(hWnd, information.c_str(), L"Information", MB_ICONINFORMATION);
}
