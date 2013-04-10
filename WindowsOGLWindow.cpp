#include "WindowsOGLWindow.h"
#include "WindowsTimer.h"

#include <GL\glew.h>
#include <GL\wglew.h>

#include <iostream>
#include <sstream>
using std::wstringstream;

WindowsOGLWindow* WindowsOGLWindow::self;

WindowsOGLWindow::WindowsOGLWindow(const wstring& title, OGLGameEngine* engine) : WindowsWindow(title)
{
	hrc = NULL;
	hdc = NULL;
	glVersion[0] = -1;
	glVersion[1] = -1;
	gameEngine = engine;

	WndProcedure = WindowsOGLWindow::WndProc;
	self = this;
}

WindowsOGLWindow::~WindowsOGLWindow(void)
{
	if(hdc != NULL){
		wglMakeCurrent(hdc, 0); // Remove the rendering context from the device context
		wglDeleteContext(hrc);  // Delete our rendering context
		ReleaseDC(hWnd, hdc);   // Release the device context from the window
	}
}

bool WindowsOGLWindow::create()
{
	if(!WindowsWindow::create()) return false;

	hdc = GetDC(hWnd); // Get the device context for our window
	if(hdc == NULL) return false;

	PIXELFORMATDESCRIPTOR pfd; // Create a new PIXELFORMATDESCRIPTOR (PFD)
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)); // Clear our  PFD
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); // Set the size of the PFD to the size of the class
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW; // Enable double buffering, opengl support and drawing to a window
	pfd.iPixelType = PFD_TYPE_RGBA; // Set our application to use RGBA pixels
	pfd.cColorBits = 32; // Give us 32 bits of color information (the higher, the more colors)
	pfd.cDepthBits = 32; // Give us 32 bits of depth information (the higher, the more depth levels)
	pfd.iLayerType = PFD_MAIN_PLANE; // Set the layer of the PFD

	int pixelFormat = ChoosePixelFormat(hdc, &pfd); // Check if our PFD is valid and get a pixel format back
	if (pixelFormat == 0) return false;

	BOOL result = SetPixelFormat(hdc, pixelFormat, &pfd); // Try and set the pixel format based on our PFD
	if (!result) return false;

	HGLRC tempOpenGLContext = wglCreateContext(hdc); // Create an OpenGL 2.1 context for our device context
	wglMakeCurrent(hdc, tempOpenGLContext);          // Make the OpenGL 2.1 context current and active

	// Enable GLEW
	if (glewInit() != GLEW_OK) return false;

	int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3, // Set the MAJOR version of OpenGL to 3
		WGL_CONTEXT_MINOR_VERSION_ARB, 1, // Set the MINOR version of OpenGL to 1
		WGL_CONTEXT_FLAGS_ARB, 
		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // Set our OpenGL context to be forward compatible
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1) { // If the OpenGL 3.x context creation extension is available
		hrc = wglCreateContextAttribsARB(hdc, NULL, attributes); // Create and OpenGL 3.x context based on the given attributes
		wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
		wglDeleteContext(tempOpenGLContext); // Delete the temporary OpenGL 2.1 context
		wglMakeCurrent(hdc, hrc);
	}
	else {
		// If we didn't have support for OpenGL 3.x and up, use the OpenGL 2.1 context
		hrc = tempOpenGLContext; 
		showMessage(L"OpenGL 3 not supported using 2.1 instead.");
	}
	
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]); // Get back the OpenGL MAJOR version we are using
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]); // Get back the OpenGL MINOR version we are using

	return true; // We have successfully created a context
}

void WindowsOGLWindow::initializeEnvironment()
{
   gameEngine->timer = new WindowsTimer();
	gameEngine->initialize();
}

void WindowsOGLWindow::processEvents()
{
	MSG msg;
   gameEngine->startTiming();
   
	while (!gameEngine->isGameOver()){
      PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		// If we have a message (event) to process, process it
		if (msg.message == WM_QUIT) {
			gameEngine->setGameOver();
		}
		else {
         runOneFrame();
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
   }
   gameEngine->timer->stop();
}

LRESULT CALLBACK WindowsOGLWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_SIZE: 
		// If our window is resizing send the new window size to our OpenGL window
		self->updateOGLViewportsize(LOWORD(lParam), HIWORD(lParam)); 
		break;
   case WM_KEYDOWN:
      self->gameEngine->inputSystem.keys[wParam] = true;
      return 0;
   case WM_KEYUP:
      self->gameEngine->inputSystem.keys[wParam] = false;
      return 0;
   case WM_LBUTTONDOWN:
      break;
   case WM_RBUTTONDOWN:
      break;
   case WM_LBUTTONUP:
      break;
   case WM_MOUSEMOVE:
      self->gameEngine->inputSystem.mouseX = LOWORD(lParam);
      self->gameEngine->inputSystem.mouseY = HIWORD(lParam);
      //if(self->gameEngine->inputSystem.mouseX < 2){
      //   BlockInput(true);
      //   SetCursorPos(self->gameEngine->windowWidth-2, self->gameEngine->inputSystem.mouseY);
      //   BlockInput(false);
      //}
      //else if(self->gameEngine->inputSystem.mouseX > self->gameEngine->windowWidth-2){
      //   BlockInput(true);
      //   SetCursorPos(2, self->gameEngine->inputSystem.mouseY);
      //   BlockInput(false);
      //}
      break;
   case WM_RBUTTONUP:
      break;
	}

	return WindowsWindow::WndProc(hWnd, message, wParam, lParam);
}

wstring WindowsOGLWindow::getOpenGLVersionInformation() const
{
	wstringstream stringStream;
	stringStream << glVersion[0] << "." << glVersion[1];
	wstring version;
	getline(stringStream, version);
	return version;
}

void WindowsOGLWindow::runOneFrame()
{
   gameEngine->playerUpdate(gameEngine->getTickTime());
   gameEngine->cameraUpdate();

   if(gameEngine->isTimeToUpdateLogic()){
      gameEngine->gameLogic(gameEngine->timer->getElapsedTimeInSeconds() * 1000);
      gameEngine->updateTimingVariables();
   }

	glViewport(0, 0, width, height); // Set the viewport size to fill the window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
   glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear required buffers
   gameEngine->gamePresentation();

	SwapBuffers(hdc); // Swap buffers so we can see our rendering
}

void WindowsOGLWindow::updateOGLViewportsize(int w, int h) 
{
	width = w; // Set the window width
	height = h; // Set the window height
   gameEngine->windowWidth = width;
   gameEngine->windowHeight = height;
	gameEngine->setAspectRatio(width / (float)height);
}
